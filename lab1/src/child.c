#include "child.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ChildRoutine(int pipe_cin[2], int pipe_out[2], void (*func)(char *str)) {
    char buffer[BUFFER_SIZE];

    close(pipe_cin[1]); 
    close(pipe_out[0]); 

    if (read(pipe_cin[0], buffer, BUFFER_SIZE) == -1) {
        perror("Ошибка при чтении из pipe");
        exit(1);
    }


    func(buffer);

    if (write(pipe_out[1], buffer, strlen(buffer) + 1) == -1) {
        perror("Ошибка при записи в pipe");
        exit(1);
    }

    close(pipe_cin[0]); 
    close(pipe_out[1]); 
}
