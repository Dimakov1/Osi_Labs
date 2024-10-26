#include "parent.h"
#include "child.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char* ParentRoutine(const char* inputString) {
    int pipe1[2];
    int pipe2[2]; 
    int pipe3[2]; 
    static char buffer[BUFFER_SIZE]; 

    Create_pipe(pipe1);
    Create_pipe(pipe2);
    Create_pipe(pipe3);

    pid_t child1 = fork();
    if (child1 == -1) {
        perror("Ошибка при вызове fork для Child1");
        exit(1);
    }

    if (child1 == 0) { 
        ChildRoutine(pipe1, pipe3, To_lower_case);
        exit(0);
    }

    pid_t child2 = fork();
    if (child2 == -1) {
        perror("Ошибка при вызове fork для Child2");
        exit(1);
    }

    if (child2 == 0) { 
        ChildRoutine(pipe3, pipe2, Replace_spaces);
        exit(0);
    }

    close(pipe1[0]); 
    close(pipe3[0]); 
    close(pipe3[1]); 
    close(pipe2[1]); 

    strncpy(buffer, inputString, BUFFER_SIZE - 1); 
    buffer[BUFFER_SIZE - 1] = '\0'; 

    if (write(pipe1[1], buffer, strlen(buffer) + 1) == -1) {
        perror("Ошибка при записи в pipe1");
        exit(1);
    }

    close(pipe1[1]);

    wait(NULL);
    wait(NULL); 

    if (read(pipe2[0], buffer, BUFFER_SIZE) == -1) {
        perror("Ошибка при чтении из pipe2");
        exit(1);
    }

    close(pipe2[0]);

    return buffer;
}
