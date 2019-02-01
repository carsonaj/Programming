#include <stdlib.h>
#include <stdbool.h>
#include "array_lib.h"

// helpful functions
int min(double a, double b) {
    if (a < b)
        return a;
    else
        return b;
//----------------------------------------------------------------------------

// array

void swap(double *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

double sum(double *arr) {
    double sum = 0;
}

// merge-sort an array

// merge two sorted subarrays arr[l,l+1,...m] arr[m+1,m+2,...,r]
void merge(double *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    //create temp arrays
    double la[n1], ra[n2];

    // copy data to temp arrays
    for (i=0; i<n1; i=i+1)
        la[i] = arr[l+i];

    for (j=0; j<n2; j=j+1)
        ra[j] = arr[m+1+j];

    // merge the temp arrays
    i = 0;
    j = 0;
    k = l;

    while (i<n1 && j<n2) {
        if (la[i] <= ra[j]){
            arr[k] = la[i];
            i = i+1;
        }
        else {
            arr[k] = ra[j];
            j = j+1;
        }
        k = k+1;
    }

    while (i<n1) {
        arr[k] = la[i];
        i = i+1;
        k = k+1;
    }

    while (j<n2) {
        arr[k] = ra[j];
        j = j+1;
        k = k+1;
    }
}

void merge_sort(double *arr, int l, int r) {
    if (l < r) {
        int m = l + (r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

//quick-sort an array

// parttion arr with pivot as last element
Tuple partition(double *arr, int l, int r) {
    int i = l, j = l, k = 0;
    while (j < r-k) {
        if (arr[j] == arr[r-k]) {
            if (arr[j] == arr[r-k-1]) {
                k = k+1;
                continue;
            }
            else {
                swap(arr, j, r-k-1);
                k = k+1;
            }
        }
        if (arr[j] < arr[r-k]) {
            if (i != j)
                swap(arr, i, j);
            i = i+1;
        }
        j = j+1;
    }

    int n, m = min(j-i-1, k);
    for (n=0; n<=m; n=n+1)
        swap(arr, i+n, r-n);

        Tuple x;
    if (k < r-l) {
        x.values[0] = i-1;
        x.values[1] = i+k+1;
    }
    else {
        x.values[0] = l;
        x.values[1] = r;
    }

    return x;
}

void quick_sort(double *arr, int l, int r) {
    if (l < r) {
        Tuple x = partition(arr, l, r);
        quick_sort(arr, l, x.values[0]);
        quick_sort(arr, x.values[1], r);
    }
}

// binary-search an array

//search

int binary_search(double *arr, int l, int r, int x) {
    if (r > l) {
        int m = l + (r-l)/2;

        if (arr[m] == x)
            return m;
        else if (arr[m]<x)
            return binary_search(arr, m+1, r, x);
        else
            return binary_search(arr, l, m, x);
    }
    else {
        if (arr[l] == x)
            return l;
        else
            return -1;
    }
}
