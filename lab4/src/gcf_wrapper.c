#include "gcf.h"

static GCF_Function current_gcf = GCF_Euclidean;

void set_gcf_function(GCF_Function func) {
    current_gcf = func;
}

GCF_Function get_gcf_function() {
    return current_gcf;
}

int GCF(int A, int B) {
    return current_gcf(A, B);
}
