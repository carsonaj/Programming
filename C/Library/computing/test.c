#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "array.h"
#include "matrix.h"
#include "linear_programming.h"

int main() {
    Matrix *A = mat_create_matrix(3, 6, false);
    double dats1[18] = {1.0,1.0,2.0,1.0,0.0,0.0, 2.0,0.0,3.0,0.0,1.0,0.0, 2.0,1.0,3.0,0.0,0.0,1.0};
    int i;
    for (i=0; i<18; i++) {
        A->data[i] = dats1[i];
    }
    int m = A->rows;
    int n = A->cols;

    Matrix *b = mat_create_matrix(3, 1, false);
    double dats2[3] = {4.0,5.0,7.0};
    for (i=0; i<3; i++) {
        b->data[i] = dats2[i];
    }

    Matrix *c = mat_create_matrix(6, 1, false);
    double dats3[6] = {3.0,2.0,4.0,0.0,0.0,0.0};
    for (i=0; i<6; i++) {
        c->data[i] = dats3[i];
    }
    Matrix *c_trans = mat_transpose(c);
    mat_delete_matrix(c);

    int *indices = start_indices(A);
    for (i=0; i<6; i++) {
        printf("%d ", indices[i]);
    }
    printf("\n");

    Matrix *B = basic_mat(A, indices);
    mat_print_matrix(B);
    printf("\n");

    Matrix *N = nonbasic_mat(A, indices);
    mat_print_matrix(N);
    printf("\n");

    Matrix *cb_trans = basic_cost_trans(c_trans, m, indices);
    Matrix *cn_trans = nonbasic_cost_trans(c_trans, m, indices);

    mat_print_matrix(cb_trans);
    printf("\n");
    mat_print_matrix(cn_trans);
    printf("\n");

    int e = entering_col(B, N, cb_trans, cn_trans);
    printf("%d\n", e);
    printf("\n");

    Matrix *xbsol = mat_create_matrix(m, m+1, false);
    int j;
    for (i=0; i<m; i++); {
        for (j=0; j<m; j++) {
            double element = mat_get_element(B, i, j);
            mat_set_element(xbsol, i, j, element);
        }
    }
    for (i=0; i<m; i++) {
        double element = mat_get_element(b, i, 0);
        mat_set_element(xbsol, i, m, element);
    }

    mat_rref(xbsol);
    Matrix *xb = mat_create_matrix(m, 1, false);
    for (i=0; i<m; i++) {
        double element = mat_get_element(xbsol, i, m);
        mat_set_element(xb, i, 0, element);
    }
    mat_delete_matrix(xbsol);

    mat_print_matrix(xb);
    printf("\n");

    Matrix *tes = mat_create_matrix(3, 4, false);
    double dats4[12] = {1.0,1.0,2.0,1.0, 2.0,0.0,3.0,0.0, 2.0,1.0,3.0,0.0};
    for (i=0; i<12; i++) {
        tes->data[i] = dats4[i];
    }
    mat_rref(tes);
    mat_print_matrix(tes);
    printf("\n");

    printf("%d\n", 0.0==mat_get_element(tes, 2, 0));

    int l = leaving_col(B, N, xb, indices, e);

    return 0;
}
