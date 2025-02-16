#ifndef SORT_H
#define SORT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Sort_Function)(int*, int);

void set_sort_function(Sort_Function func);

Sort_Function get_sort_function();

void Sort(int* array, int size);

void Sort_Bubble(int* array, int size);
void Sort_Quick(int* array, int size);

#ifdef __cplusplus
}
#endif

#endif 
