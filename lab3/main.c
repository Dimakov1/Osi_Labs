#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/memory_map.h"
#include "include/processes.h"
#include "include/error_handling.h"

#define BUFFER_SIZE 1024

int main() {
    char *shared_mem = create_shared_memory(BUFFER_SIZE);

    printf("Enter a string: ");
    if (fgets(shared_mem, BUFFER_SIZE, stdin) == NULL) {
        handle_error("Failed to read input");
    }
    shared_mem[strcspn(shared_mem, "\n")] = '\0';

    pid_t pid1 = fork();
    if (pid1 < 0) {
        handle_error("fork failed for Child1");
    } else if (pid1 == 0) {
        child1(shared_mem);
    }

    waitpid(pid1, NULL, 0);

    pid_t pid2 = fork();
    if (pid2 < 0) {
        handle_error("fork failed for Child2");
    } else if (pid2 == 0) {
        child2(shared_mem);
    }

    waitpid(pid2, NULL, 0);
    printf("Parent: Final result: %s\n", shared_mem);

    release_shared_memory(shared_mem, BUFFER_SIZE);

    return 0;
}
