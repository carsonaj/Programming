#include <stdlib.h>

// helpful functions

int min(double a, double b);
//-------------------------------------------------------------------------

// array
int min(double a, double b);

void swap(double *arr, int i, int j);
double sum(double *arr)

// merge-sort an array
void merge(double *arr, int l, int m, int r);
void merge_sort(double *arr, int l, int r);

//quick-sort an array
typedef struct _Tuple Tuple;

struct _Tuple {
    int values[2];
};

Tuple partition(double *arr, int l, int r);
void quick_sort(double *arr, int l, int r);

// binary-search an array
int binary_search(double *arr, int l, int r, int x);
