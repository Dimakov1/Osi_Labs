#ifndef PROCESSES_H
#define PROCESSES_H

#include <stddef.h>
void init_child_process(int BUFFER_SIZE);
void child1(char *shared_mem);
void child2(char *shared_mem);
int process_string(const char *input, char *output, size_t size);

#endif 
