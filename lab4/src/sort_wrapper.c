#include "sort.h"

static Sort_Function current_sort = Sort_Bubble; 

void set_sort_function(Sort_Function func) {
    current_sort = func;
}

Sort_Function get_sort_function() {
    return current_sort;
}

void Sort(int* array, int size) {
    current_sort(array, size);
}
