#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "memory_map.h"
#include "processes.h"
#include "error_handling.h"

#define BUFFER_SIZE 1024

int main() {
    init_child_process(BUFFER_SIZE);
    wait(NULL);  
    return 0;
}
