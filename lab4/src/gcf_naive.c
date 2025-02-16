#include "gcf.h"

int GCF_Naive(int A, int B) {
    if (A == 0 && B == 0) {
        return 0;
    }
    if (A == 0) {
        return (B > 0) ? B : -B;
    }
    if (B == 0) {
        return (A > 0) ? A : -A;
    }

    if (A < 0) A = -A;
    if (B < 0) B = -B;

    int min = (A < B) ? A : B;
    int gcf = 1;
    for (int i = 1; i <= min; ++i) {
        if (A % i == 0 && B % i == 0) {
            gcf = i;
        }
    }
    return gcf;
}
