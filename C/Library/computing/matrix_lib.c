#include <stdlib.h>
#include <stdbool.h>
#include "matrix_lib.h"


// zero indexed matrix library


// structure
Matrix *create_matrix(int rows, int cols, bool zeros) {
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

void delete_matrix(Matrix *mat) {
    free(mat->data);
    free(mat);
}

double get_element(Matrix *mat, int row, int col) {
    return mat->data[row*(mat->cols) + col];
}

void set_element(Matrix *mat, int row, int col, double element) {
    mat->data[row*(mat->cols) + col] = element;
}

Matrix *get_row(Matrix *mat, int row) {
    int rows = 1;
    int cols = mat->cols;
    Matrix *row_mat = create_matrix(rows, cols, false);

    int j;
    for (j=0; j<cols; j=j+1) {
        double element = get_element(mat, row, j);
        set_element(row_mat, 0, j, element);
    }

    return row_mat;
}

Matrix *get_col(Matrix *mat, int col) {
    int rows = mat->rows;
    int cols = 1;
    Matrix *col_mat = create_matrix(rows, cols, false);

    int i;
    for (i=0; i<rows; i=i+1) {
        double element = get_element(mat, i, col);
        set_element(col_mat, i, 0, element);
    }

    return col_mat;
}

// elementary row operations:

// (type 1) swaps rows i,j
void row_op1(Matrix *mat, int i, int j) {
    int cols = mat->cols;
    Matrix *temp_i = get_row(mat, i);
    int col;
    for (col=0; col<cols; col=col+1) {
        double element_j = get_element(mat, j, col);
        set_element(mat, i, col, element_j);
        double element_i = get_element(temp_i, 0, col);
        set_element(mat, j, col, element_i);
    }

    delete_matrix(temp_i);
}

// (type 2) multiplies row i by a constant k
void row_op2(Matrix *mat, int i, double k) {
    int cols = mat->cols;
    int j;
    for (j=0; j<cols; j=j+1) {
        double element = k*get_element(mat, i, j);
        set_element(mat, i, j, element);
    }
}

// (type 3) multiplies row j by constant k and adds it to row i
void row_op3(Matrix *mat, int i, int j, double k) {
    int cols = mat->cols;
    int col;
    for (col=0; col<cols; col=col+1) {
        double element = get_element(mat, i, col) + k*get_element(mat, j, col);
        set_element(mat, i, col, element);
    }
}

//------------------------------------------------------------------------

// mathematics
bool equal(Matrix *A, Matrix *B) {
    bool same_rows = (A->rows == B->rows);
    bool same_cols = (A->cols == B->cols);
    if (!same_rows || !same_cols) {
        return false;
    }

    int rows = A->rows;
    int cols = A->cols;
    int i;
    for (i=0, i<rows*cols, i=i+1) {
        if (A->data[i] != B->data[i]) {
            return false;
        }
        else
            return true;
    }

}

Matrix *product(Matrix *A, Matrix *B) {
    assert(A->cols == B->rows);
    int m,n,p;
    m = A->rows;
    n = A->cols;
    p = B->cols;

    Matrix *mat = new_matrix(m, p);
    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<p; j=j+1) {

            double kron_prod[n];
            int k;
            for (k=0; k<n; k=k+1) {
                kron_prod[k] = get_element(A, i, k)*get_element(B, k, j);
            }

            element = sum(kron_prod);
            set_element(mat, i, j, element);
        }
    }

    return mat;
}

Matrix *sum(Matrix *A, Matrix *B) {
    assert(A->rows == B->rows);
    assert(A->cols == B->cols);
    int m = A->cols;
    int n = B->cols;

    Matrix *mat = new_matrix(m, n);
    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            element = get_element(A, i, j) + get_element(B, i, j);
            set_element(mat, i, j, element);
        }
    }

    return mat;
}


//----------------------------------------------------------------------

// algorithms

// row echelon form
void sub_ref(Matrix *mat, int start_row, int start_col) {

    // check if mat is zero matrix
    int rows = mat->rows;
    int cols = mat->cols;
    bool val = true;
    double element;
    int row = start_row;
    int col = start_col;
    while (col<cols) {
        while (row<rows) {
            element = get_element(mat, row, col);
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
    row_op2(mat, row, 1.0/element);
    row_op1(mat, start_row, row);
    row = row+1;
    while (row<rows) {
        double k = -get_element(mat, row, col);
        row_op3(mat, row, start_row, k);
    }
    // recursive call on submatrix down-right from pivot
    sub_ref(mat, start_row+1, col+1);
}

void ref(Matrix *mat) {
    sub_ref(mat, 0, 0);
}

// reduced row echelon form
void sub_rref(Matrix *mat, int start_row, int start_col) {
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
            element = get_element(mat, row, col);
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
    element = -get_element(mat, prev_row, col);
    while (0<=prev_row) {
        if (element != 0)
            row_op3(mat, prev_row, row, element);
    }

    row = row+1;
    col = col+1;
    sub_ref(mat, row, col);
}

void rref(Matrix *mat) {
    ref(mat);
    sub_ref(mat, 0, 0);
}
