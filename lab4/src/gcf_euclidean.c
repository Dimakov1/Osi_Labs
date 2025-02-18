#include "gcf.h"

int GCF_Euclidean(int A, int B) {
    while (B != 0) {
        int temp = B;
        B = A % B;
        A = temp;
    }
    return A;
}
