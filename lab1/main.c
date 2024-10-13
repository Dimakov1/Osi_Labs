#include "parent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(void) {
    char buffer[BUFFER_SIZE];

    printf("Введите строку: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        perror("Ошибка при вводе данных");
        exit(1);
    }
    buffer[strcspn(buffer, "\n")] = '\0'; 

    char* result = ParentRoutine(buffer);

    printf("Результат     : %s\n", result);

    return 0;
}
