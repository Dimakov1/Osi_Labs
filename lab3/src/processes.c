#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "error_handling.h"
#include "memory_map.h"
#include "processes.h"

void init_child_process(int BUFFER_SIZE) {
    pid_t pid = fork();
    if (pid < 0) {
        handle_error("fork error");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        char input[BUFFER_SIZE];
        char output[BUFFER_SIZE];

        while (1) {
            printf("Введите строку (или нажмите Ctrl+D для завершения): ");
            if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
                break;
            }
            input[strcspn(input, "\n")] = '\0';

            int result = process_string(input, output, BUFFER_SIZE);
            if (result != 0) {
                handle_error("Не удалось обработать строку");
            }

            printf("Результат обработки: %s\n", output);
        }
        exit(0);
    }
}

void child1(char *shared_mem) {
    for (int i = 0; shared_mem[i] != '\0'; i++) {
        shared_mem[i] = tolower(shared_mem[i]);
    }
}

void child2(char *shared_mem) {
    for (int i = 0; shared_mem[i] != '\0'; i++) {
        if (shared_mem[i] == ' ') {
            shared_mem[i] = '_';
        }
    }
}

int process_string(const char *input, char *output, size_t size) {
    if (size < strlen(input) + 1) {
        return -1;
    }

    char *shared_mem = create_shared_memory(size);
    if (!shared_mem) {
        return -1;
    }

    strncpy(shared_mem, input, size - 1);
    shared_mem[size - 1] = '\0';

    child1(shared_mem);
    child2(shared_mem);

    strncpy(output, shared_mem, size - 1);
    output[size - 1] = '\0';

    release_shared_memory(shared_mem, size);

    return 0;
}
