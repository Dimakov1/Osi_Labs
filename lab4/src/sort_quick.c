#include "sort.h"

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low -1;
    for (int j = low; j < high; ++j) {
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    return i+1;
}

void quick_sort(int* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quick_sort(array, low, pi -1);
        quick_sort(array, pi +1, high);
    }
}

void Sort_Quick(int* array, int size) {
    quick_sort(array, 0, size -1);
}
