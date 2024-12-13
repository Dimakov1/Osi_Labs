#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "gcf.h"
#include "sort.h"

typedef void (*SetGCFFunction)(GCF_Function);
typedef void (*SetSortFunction)(Sort_Function);
typedef GCF_Function (*GetGCFFunction)();
typedef Sort_Function (*GetSortFunction)();
typedef int (*GCF)(int, int);
typedef void (*Sort)(int*, int);

int main() {
    void* handle_gcf = dlopen("libgcf.so", RTLD_LAZY);
    if (!handle_gcf) {
        fprintf(stderr, "Ошибка загрузки libgcf.so: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    void* handle_sort = dlopen("libsort.so", RTLD_LAZY);
    if (!handle_sort) {
        fprintf(stderr, "Ошибка загрузки libsort.so: %s\n", dlerror());
        dlclose(handle_gcf);
        exit(EXIT_FAILURE);
    }

    dlerror();

    SetGCFFunction set_gcf_function = (SetGCFFunction)dlsym(handle_gcf, "set_gcf_function");
    char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска set_gcf_function: %s\n", error);
        dlclose(handle_gcf);
        dlclose(handle_sort);
        exit(EXIT_FAILURE);
    }

    SetSortFunction set_sort_function = (SetSortFunction)dlsym(handle_sort, "set_sort_function");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска set_sort_function: %s\n", error);
        dlclose(handle_gcf);
        dlclose(handle_sort);
        exit(EXIT_FAILURE);
    }

    GCF GCF_func = (GCF)dlsym(handle_gcf, "GCF");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска GCF: %s\n", error);
        dlclose(handle_gcf);
        dlclose(handle_sort);
        exit(EXIT_FAILURE);
    }

    Sort Sort_func = (Sort)dlsym(handle_sort, "Sort");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска Sort: %s\n", error);
        dlclose(handle_gcf);
        dlclose(handle_sort);
        exit(EXIT_FAILURE);
    }

    printf("Динамическая загрузка библиотек успешна.\n");

    set_gcf_function(GCF_Euclidean);
    set_sort_function(Sort_Bubble);

    char command[256];
    while (1) {
        printf("\nВведите команду:\n");
        printf("0 - переключить реализации функций\n");
        printf("1 A B - вычислить GCF(A, B)\n");
        printf("2 size elem1 elem2 ... elemN - отсортировать массив\n");
        printf("q - выход\n");
        printf("Команда: ");
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "q") == 0) {
            break;
        }

        if (strcmp(command, "0") == 0) {
            static int gcf_switch = 0;
            if (gcf_switch == 0) {
                set_gcf_function(GCF_Naive);
                printf("Реализация GCF переключена на Naive.\n");
                gcf_switch = 1;
            } else {
                set_gcf_function(GCF_Euclidean);
                printf("Реализация GCF переключена на Euclidean.\n");
                gcf_switch = 0;
            }

            static int sort_switch = 0;
            if (sort_switch == 0) {
                set_sort_function(Sort_Quick);
                printf("Реализация Sort переключена на Quick Sort.\n");
                sort_switch = 1;
            } else {
                set_sort_function(Sort_Bubble);
                printf("Реализация Sort переключена на Bubble Sort.\n");
                sort_switch = 0;
            }

            continue;
        }

        char* token = strtok(command, " ");
        if (token == NULL) {
            continue;
        }

        if (strcmp(token, "1") == 0) {
            char* arg1 = strtok(NULL, " ");
            char* arg2 = strtok(NULL, " ");
            if (arg1 == NULL || arg2 == NULL) {
                printf("Недостаточно аргументов для команды 1.\n");
                continue;
            }
            int A = atoi(arg1);
            int B = atoi(arg2);

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            int result = GCF_func(A, B);
            clock_gettime(CLOCK_MONOTONIC, &end);

            double time_taken = (end.tv_sec - start.tv_sec) * 1e3 +
                                (end.tv_nsec - start.tv_nsec) / 1e6; 

            printf("GCF(%d, %d) = %d\n", A, B, result);
            printf("Время выполнения GCF: %.6f ms\n", time_taken);
        }
        else if (strcmp(token, "2") == 0) {
            char* arg_size = strtok(NULL, " ");
            if (arg_size == NULL) {
                printf("Недостаточно аргументов для команды 2.\n");
                continue;
            }
            int size = atoi(arg_size);
            if (size <= 0) {
                printf("Некорректный размер массива.\n");
                continue;
            }
            int* array = malloc(size * sizeof(int));
            if (!array) {
                printf("Не удалось выделить память для массива.\n");
                continue;
            }
            int valid = 1;
            for (int i = 0; i < size; ++i) {
                char* elem = strtok(NULL, " ");
                if (elem == NULL) {
                    printf("Недостаточно элементов для массива.\n");
                    free(array);
                    valid = 0;
                    break;
                }
                array[i] = atoi(elem);
            }
            if (!valid) {
                continue;
            }

            printf("Исходный массив: ");
            for(int i = 0; i < size; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");

            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);
            Sort_func(array, size);
            clock_gettime(CLOCK_MONOTONIC, &end);

            double time_taken = (end.tv_sec - start.tv_sec) * 1e3 +
                                (end.tv_nsec - start.tv_nsec) / 1e6; 

            printf("Отсортированный массив: ");
            for(int i = 0; i < size; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");
            printf("Время выполнения сортировки: %.6f ms\n", time_taken);

            free(array);
        }
        else {
            printf("Неизвестная команда.\n");
        }
    }

    dlclose(handle_gcf);
    dlclose(handle_sort);

    return 0;
}
