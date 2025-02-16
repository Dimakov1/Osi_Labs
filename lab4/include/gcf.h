#ifndef GCF_H
#define GCF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*GCF_Function)(int, int);

void set_gcf_function(GCF_Function func);

GCF_Function get_gcf_function();

int GCF(int A, int B);

int GCF_Euclidean(int A, int B);
int GCF_Naive(int A, int B);

#ifdef __cplusplus
}
#endif

#endif
