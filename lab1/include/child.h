#ifndef CHILD_H
#define CHILD_H

void ChildRoutine(int pipe_cin[2], int pipe_out[2], void (*func)(char *str));

#endif 
