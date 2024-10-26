#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void Create_pipe(int pipeFd[2]) {
    if (pipe(pipeFd) == -1) {
        perror("Ошибка при создании pipe");
        exit(1);
    }
}

void To_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void Replace_spaces(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}
