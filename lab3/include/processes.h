#ifndef PROCESSES_H
#define PROCESSES_H

#include <stddef.h>

void child1(char *shared_mem);
void child2(char *shared_mem);
int process_string(const char *input, char *output, size_t size);

#endif 
