#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "processes.h"

void child1(char *shared_mem) {
    for (int i = 0; shared_mem[i] != '\0'; i++) {
        shared_mem[i] = tolower(shared_mem[i]);
    }
    exit(EXIT_SUCCESS);
}

void child2(char *shared_mem) {
    for (int i = 0; shared_mem[i] != '\0'; i++) {
        if (shared_mem[i] == ' ') {
            shared_mem[i] = '_';
        }
    }
    exit(EXIT_SUCCESS);
}
    