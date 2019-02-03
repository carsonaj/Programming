#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "matrix.h"
#include "array.h"


// zero indexed matrix library


// structure
Matrix *mat_create_matrix(int rows, int cols, bool zeros) {
    Matrix *mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;

    int length = rows*cols;
    mat->data = malloc(length*sizeof(double));

    if (zeros == true) {
        int i;
        for (i=0; i<length; i=i+1) {
            mat->data[i] = 0.0;
        }
    }

    return mat;
}

void mat_delete_matrix(Matrix *mat) {
    free(mat->data);
    free(mat);
}

double mat_get_element(Matrix *mat, int row, int col) {
    return mat->data[row*(mat->cols) + col];
}

void mat_set_element(Matrix *mat, int row, int col, double element) {
    mat->data[row*(mat->cols) + col] = element;
}

Matrix *mat_get_row(Matrix *mat, int row) {
    int rows = 1;
    int cols = mat->cols;
    Matrix *row_mat = mat_create_matrix(rows, cols, false);

    int j;
    for (j=0; j<cols; j=j+1) {
        double element = mat_get_element(mat, row, j);
        mat_set_element(row_mat, 0, j, element);
    }

    return row_mat;
}

Matrix *mat_get_col(Matrix *mat, int col) {
    int rows = mat->rows;
    int cols = 1;
    Matrix *col_mat = mat_create_matrix(rows, cols, false);

    int i;
    for (i=0; i<rows; i=i+1) {
        double element = mat_get_element(mat, i, col);
        mat_set_element(col_mat, i, 0, element);
    }

    return col_mat;
}

// elementary row operations:

// (type 1) swaps rows i,j
void mat_row_op1(Matrix *mat, int i, int j) {
    int cols = mat->cols;
    Matrix *temp_i = mat_get_row(mat, i);
    int col;
    for (col=0; col<cols; col=col+1) {
        double element_j = mat_get_element(mat, j, col);
        mat_set_element(mat, i, col, element_j);
        double element_i = mat_get_element(temp_i, 0, col);
        mat_set_element(mat, j, col, element_i);
    }

    mat_delete_matrix(temp_i);
}

// (type 2) multiplies row i by a constant k
void mat_row_op2(Matrix *mat, int i, double k) {
    int cols = mat->cols;
    int j;
    for (j=0; j<cols; j=j+1) {
        double element = k*mat_get_element(mat, i, j);
        mat_set_element(mat, i, j, element);
    }
}

// (type 3) multiplies row j by constant k and adds it to row i
void mat_row_op3(Matrix *mat, int i, int j, double k) {
    int cols = mat->cols;
    int col;
    for (col=0; col<cols; col=col+1) {
        double element = mat_get_element(mat, i, col) + k*mat_get_element(mat, j, col);
        mat_set_element(mat, i, col, element);
    }
}

//------------------------------------------------------------------------

// mathematics
bool mat_equal(Matrix *A, Matrix *B) {
    bool same_rows = (A->rows == B->rows);
    bool same_cols = (A->cols == B->cols);
    if (!same_rows || !same_cols) {
        return false;
    }

    int rows = A->rows;
    int cols = A->cols;
    int i;
    for (i=0; i<rows*cols; i=i+1) {
        if (A->data[i] != B->data[i])
            return false;
    }

    return true;
}

Matrix *mat_product(Matrix *A, Matrix *B) {
    assert(A->cols == B->rows);
    int m,n,p;
    m = A->rows;
    n = A->cols;
    p = B->cols;

    Matrix *mat = mat_create_matrix(m, p, false);
    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<p; j=j+1) {

            double kron_prod[n];
            int k;
            for (k=0; k<n; k=k+1) {
                kron_prod[k] = mat_get_element(A, i, k)*mat_get_element(B, k, j);
            }

            double element = arr_sum(kron_prod, n);
            mat_set_element(mat, i, j, element);
        }
    }

    return mat;
}

Matrix *mat_sum(Matrix *A, Matrix *B) {
    assert(A->rows == B->rows);
    assert(A->cols == B->cols);
    int m = A->cols;
    int n = B->cols;

    Matrix *mat = mat_create_matrix(m, n, false);
    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            double element = mat_get_element(A, i, j) + mat_get_element(B, i, j);
            mat_set_element(mat, i, j, element);
        }
    }

    return mat;
}


//----------------------------------------------------------------------

// algorithms

// row echelon form
static void sub_ref(Matrix *mat, int start_row, int start_col) {

    // check if mat is zero matrix
    int rows = mat->rows;
    int cols = mat->cols;
    bool val = true;
    double element;
    int row = start_row;
    int col = start_col;
    while (col<cols) {
        while (row<rows) {
            element = mat_get_element(mat, row, col);
            if (element != 0) {
                val = false;
                break;
            }
            row = row+1;
        }
        if (!val)
            break;
        col = col+1;
    }
    if (val)
        return;

    // row operations to creat a pivot of 1 and zeros below pivot
    mat_row_op2(mat, row, 1.0/element);
    mat_row_op1(mat, start_row, row);
    row = row+1;
    while (row<rows) {
        double k = -mat_get_element(mat, row, col);
        mat_row_op3(mat, row, start_row, k);
    }
    // recursive call on submatrix down-right from pivot
    sub_ref(mat, start_row+1, col+1);
}

void mat_ref(Matrix *mat) {
    sub_ref(mat, 0, 0);
}

// reduced row echelon form
static void sub_rref(Matrix *mat, int start_row, int start_col) {
    // assume matrix is in row echelon form
    // check if mat is zero matrix
    int rows = mat->rows;
    int cols = mat->cols;
    bool val = true;
    double element;
    int row = start_row;
    int col = start_col;
    while (col<cols) {
        while (row<rows) {
            element = mat_get_element(mat, row, col);
            if (element != 0) {
                val = false;
                break;
            }
            row = row+1;
        }
        if (!val)
            break;
        col = col+1;
    }
    if (val)
        return;

    // now (row, col) is the pivot
    int prev_row = row-1;
    element = -mat_get_element(mat, prev_row, col);
    while (0<=prev_row) {
        if (element != 0)
            mat_row_op3(mat, prev_row, row, element);
    }

    row = row+1;
    col = col+1;
    sub_rref(mat, row, col);
}

void mat_rref(Matrix *mat) {
    mat_ref(mat);
    sub_rref(mat, 0, 0);
}
