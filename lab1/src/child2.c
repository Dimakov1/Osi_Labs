#include "child2.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Child2Routine(int pipe3[2], int pipe2[2]) {
    char buffer[BUFFER_SIZE];

    close(pipe3[1]); 
    close(pipe2[0]);

    if (read(pipe3[0], buffer, BUFFER_SIZE) == -1) {
        perror("Ошибка при чтении из pipe3");
        exit(1);
    }

    replace_spaces(buffer);

    if (write(pipe2[1], buffer, strlen(buffer) + 1) == -1) {
        perror("Ошибка при записи в pipe2");
        exit(1);
    }

    close(pipe3[0]); 
    close(pipe2[1]); 
}
