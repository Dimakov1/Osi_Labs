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

    pid_t pid1 = fork();
    if (pid1 < 0) {
        release_shared_memory(shared_mem, size);
        return -1;
    } else if (pid1 == 0) {
        child1(shared_mem);
    }

    int status1;
    if (waitpid(pid1, &status1, 0) == -1) {
        release_shared_memory(shared_mem, size);
        return -1;
    }
    if (!(WIFEXITED(status1) && WEXITSTATUS(status1) == 0)) {
        release_shared_memory(shared_mem, size);
        return -1;
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        release_shared_memory(shared_mem, size);
        return -1;
    } else if (pid2 == 0) {
        child2(shared_mem);
    }

    int status2;
    if (waitpid(pid2, &status2, 0) == -1) {
        release_shared_memory(shared_mem, size);
        return -1;
    }
    if (!(WIFEXITED(status2) && WEXITSTATUS(status2) == 0)) {
        release_shared_memory(shared_mem, size);
        return -1;
    }

    strncpy(output, shared_mem, size - 1);
    output[size - 1] = '\0';

    release_shared_memory(shared_mem, size);

    return 0;
}
