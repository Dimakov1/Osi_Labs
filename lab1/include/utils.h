#ifndef UTILS_H
#define UTILS_H

#define BUFFER_SIZE 256

void CreatePipe(int pipeFd[2]);
void to_lower_case(char *str);
void replace_spaces(char *str);

#endif
