#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "array.h"
#include "matrix.h"

// A is a mxn matrix, m<=n (m=n has only one single feasible solution,
// so we just worry about the case m<n);
// A corresponds to a linear program in standard form;
// assume rows of A are independent;
// c is a nx1 column matrix, b is an mx1 column matrix,
// but we implement mostly with c transpose, a 1xn row matrix
// to save time/memory

// separate indices for cols that form a basis of column
// space and those that do not by array swapping; this means
// we need m basic indices at the beginning of the array
// since row space and col space have same dimension
static int *start_indices(Matrix *A) {
    int m = A->rows;
    int n = A->cols;
    Matrix *cpy = mat_copy_matrix(A);
    mat_rref(cpy);

    int *indices = malloc(n*sizeof(int));
    int l;
    for (l=0; l<n; l++) {
        indices[l] = l;
    }

    int i = 0;
    int j = 0;
    int k = 0;
    while (i<m) {
        while (j<n) {
            if (mat_get_element(cpy, i, j) == 1) {
                arr_intswap(indices, j, k);
                j = j+1;
                k = k+1;
                break;
            }
            else
                j = j+1;
        }
        i = i+1;
    }

    mat_delete_matrix(cpy);
    return indices;
}

static Matrix *basic_mat(Matrix *A, int *indices) {
    int m = A->rows;
    int n = A->cols;
    assert(m<n);
    int cols_arr[m];

    int i;
    for (i=0; i<m; i++) {
        cols_arr[i] = indices[i];
    }

        Matrix *B = mat_get_cols(A, m, cols_arr);
        return B;
}

static Matrix *nonbasic_mat(Matrix *A, int *indices) {
    int m = A->rows;
    int n = A->cols;
    assert(m<n);
    int cols_arr[n-m];

    int i;
    for(i=0; i<n-m; i++) {
        cols_arr[i] = indices[m+i];
    }

    Matrix *N = mat_get_cols(A, n-m, cols_arr);
    return N;
}

static Matrix *basic_cost(Matrix *c_trans, int m, int *indices) {
    int n = c_trans->cols;
    assert(m<n);
    int cols_arr[m];

    int i;
    for(i=0; i<m; i++) {
        cols_arr[i] = indices[i];
    }

    Matrix *cb_trans = mat_get_cols(c, m, cols_arr);
    return cb_trans;
}

static Matrix *nonbasic_cost(Matrix *c_trans, int m, int *indices) {
    int n = c_trans->cols;
    assert(m<n);
    int cols_arr[n-m];

    int i;
    for (i=0; i<n-m; i++) {
        cols_arr[i] = indices[m+i];
    }

    Matrix *cn_trans = mat_get_cols(c_trans, n-m, cols_arr);
    return cn_trans;
}

static int entering_col(Matrix *B, Matrix *N, Matrix *cb_trans, Matrix *cn_trans) {
    int m = B->rows;
    int n = (N->cols)+m;
    Matrix *ysol = mat_create_matrix(m, m+1, false);
    Matrix *y_trans = mat_create_matrix(1, m, false);
    int i, j;
    for (i=0; i<m; i++) {
        for (j=0; j<m; j++) {
            double element = mat_get_element(B, j, i);
            mat_set_element(ysol, i, j, element);
        }
    }
    for (i=0; i<m; i++) {
        double element = mat_get_element(cb_trans, 0, i);
        mat_set_element(ysol, i, m, element);
    }

    mat_rref(ysol);
    for (i=0; i<m; i++) {
        double element = mat_get_element(ysol, i, m);
        mat_set_element(y_trans, 0, i, element);
    }
    mat_delete_matrix(ysol);

    y_transN = mat_product(y_trans, N);
    minus_c_trans = mat_scalar_poduct(-1.0, cn_trans);
    zn_trans = mat_sum(y_tansN, minus_cn_trans);

    mat_delete_matrix(y_trans);
    mat_delete_matrix(y_transN);
    mat_delete_matrix(minus_cn_trans);

    int val = 0;
    i = 0;
    while (i<n-m) {
        if (zn_trans[i]) < 0 {
            val = 1;
            break
        }
        i = i+1;
    }

    // the index of the associated column in A is indices[m+i]
    if (val==0)
        return -1;
    else
        return i;
}

static leaving_col(Matrix *B, int e) {
    int cols_arr[1] = {e}
    Matrix *Ae = mat_get_cols(N, 1, cols_arr);
    Matrix *dsol = mat_create_matrix(m, m+1, false);

    int i, j;
    for (i=0; i<m; i++) {
        for (j=0; j<m; j++) {
            double element = mat_get_element(B, i, j);
            mat_set_element(dsol, i, j, element);
        }
    }
    for (i=0; i<m; i++) {
        double element = mat_get_element(Ae, i, 0);
        mat_set_element(dsol, i, m, element);
    }

    mat_rref(dsol);
    Matrix *d = mat_create_matrix(m, 1, false);
    for (i=0; i<m; i++) {
        double element = mat_get_element(dsol, i, m);
        mat_set_element(d, i, 0, element);
    }

    mat_delete_matrix(dsol);
    
}

Matrix *lp_simplex(Matrix *c, Matrix *A, Matrix *b) {

}
