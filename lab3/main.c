#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_map.h"
#include "processes.h"
#include "error_handling.h"

#define BUFFER_SIZE 1024

int main() {
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

    return 0;
}
