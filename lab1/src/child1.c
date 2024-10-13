#include "child1.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Child1Routine(int pipe1[2], int pipe3[2]) {
    char buffer[BUFFER_SIZE];

    close(pipe1[1]); 
    close(pipe3[0]); 

    if (read(pipe1[0], buffer, BUFFER_SIZE) == -1) {
        perror("Ошибка при чтении из pipe1");
        exit(1);
    }


    to_lower_case(buffer);

    if (write(pipe3[1], buffer, strlen(buffer) + 1) == -1) {
        perror("Ошибка при записи в pipe3");
        exit(1);
    }

    close(pipe1[0]); 
    close(pipe3[1]); 
}
