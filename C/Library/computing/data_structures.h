#include <stdlib.h>

// helpful functions

int min(double a, double b);
//-------------------------------------------------------------------------

// array

void swap(double *arr, int i, int j);
double sum(double *arr,int );

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
//------------------------------------------------------------------

// matrix

typedef struct _Matrix Matrix;

struct _Matrix {
    int rows;
    int cols;
    double *data;
};

Matrix *new_matrix(int rows, int cols);
double get_element(Matrix *mat, int row, int col);
void set_element(Matrix *mat, int row, int col, double element);
Matrix *product(Matrix *A, Matrix *B);
Matrix *matrixSum(Matrix*,Matrix*);
//-------------------------------------------------------------------

// linked list node

typedef struct _Lnode Lnode;

struct _Lnode {
    double data;
    struct _Lnode *next;
};

void init_Lnode(Lnode *node);
//----------------------------------------------------------------------------

//binary tree node

typedef struct _Bnode Bnode;

struct _Bnode {
    int data;
    struct _Bnode *parent;
    struct _Bnode *left;
    struct _Bnode *right;
};

void init_Bnode(Bnode *node);
void append_Bnode(Bnode *child, Bnode *parent, int side);
//----------------------------------------------------------------------------
