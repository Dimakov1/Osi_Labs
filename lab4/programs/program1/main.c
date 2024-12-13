#include <stdio.h>
#include "gcf.h"
#include "sort.h"

int main() {
    set_gcf_function(GCF_Euclidean);
    
    set_sort_function(Sort_Bubble);
    
    int A = 48, B = 18;
    int gcf = GCF(A, B);
    printf("GCF(%d, %d) = %d\n", A, B, gcf);
    
    int array[] = {5, 2, 9, 1, 5, 6};
    int size = sizeof(array)/sizeof(array[0]);
    
    printf("Original array: ");
    for(int i=0; i<size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    Sort(array, size);
    
    printf("Sorted array:   ");
    for(int i=0; i<size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    return 0;
}
