#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <assert.h>
#include "array.h"
#include "counting.h"
#include "polynomial.h"

// helpful functions
static Polynomial *max_deg(Polynomial *p1, Polynomial *p2) {
    int deg1 = p1->deg;
    int deg2 = p2->deg;
    if (deg1>deg2)
        return p1;
    else
        return p2;
}

static Polynomial *min_deg(Polynomial *p1, Polynomial *p2) {
    int deg1 = p1->deg;
    int deg2 = p2->deg;
    if (deg1>deg2)
        return p2;
    else
        return p1;
}

// data structure
Polynomial *ply_create_poly(int deg) {
    Polynomial *poly = malloc(sizeof(Polynomial));
    poly->deg = deg;

    double *coef = malloc((deg+1)*sizeof(double));
    poly->coefs = coef;

    return poly;
}

void ply_delete_poly(Polynomial *poly) {
    free(poly->coefs);
    free(poly);
}

double ply_get_coef(Polynomial *poly, int i) {
    return poly->coefs[i];
}

void ply_set_coef(Polynomial *poly, int i, double val) {
    poly->coefs[i] = val;
}

void ply_print_poly(Polynomial *poly) {
    int deg = poly->deg;
    double coef0 = ply_get_coef(poly, 0);
    double coefn = ply_get_coef(poly, deg);
    if (deg!=0)
        assert(coefn!=0);
    int i;
    if (coef0!=0)
        printf("%.2f ", coef0);
    for (i=1; i<deg; i++) {
        double coef = ply_get_coef(poly, i);
        if (coef>0) {
            printf("+ %.2fx^%d ", coef, i);
        }
        else if (coef<0)
            printf("- %.2fx^%d ", -coef, i);
    }
    if (coefn>0)
        printf("+ %.2fx^%d\n", coefn, deg);
    else
        printf("- %.2fx^%d\n", -coefn, deg);

}
//----------------------------------------------------------------------------

//mathematics

// Horner's method
double ply_evaluate(Polynomial *poly, double x) {
    int deg = poly->deg;
    double coefn = ply_get_coef(poly, deg);
    assert(coefn!=0);

    double val = coefn;
    if (deg==0) {;
        return val;
    }
    else if (deg>0) {
        while (deg>0) {
            val = val*x + ply_get_coef(poly, deg-1);
            deg = deg-1;
        }
    }

    return val;
}

// algebra

Polynomial *ply_sum(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *p1 = max_deg(poly1, poly2);
    Polynomial *p2 = min_deg(poly1, poly2);
    int deg1 = p1->deg;
    int deg2 = p2->deg;

    double sum_coefs[deg1+1];
    int i;
    for (i=0; i<=deg2; i++) {
        sum_coefs[i] = ply_get_coef(poly1, i) + ply_get_coef(poly2, i);
    }
    for (i=deg2+1; i<=deg1; i++) {
        sum_coefs[i] = ply_get_coef(p1, i);
    }
    int deg = deg1;
    while (deg>=0) {
        if (sum_coefs[deg]!=0)
            break;
        if (deg==0)
            break;
        deg = deg-1;
    }

    Polynomial *sum_poly = ply_create_poly(deg);
    for (i=0; i<=deg; i++) {
        double coef = sum_coefs[i];
        ply_set_coef(sum_poly, i, coef);
    }

    return sum_poly;

}

Polynomial *ply_product(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *p1 = max_deg(poly1, poly2);
    Polynomial *p2 = min_deg(poly1, poly2);
    int deg1 = p1->deg;
    int deg2 = p2->deg;
    int deg = deg1+deg2;

    int k;
    Polynomial *prod_poly = ply_create_poly(deg);
    for (k=0; k<=deg; k++) {
        double sum_k = 0;
            int l;
            for (l=0; l<=k; l++) {
                if ((l<=deg1)&&(k-l<=deg2))
                    sum_k = sum_k+(ply_get_coef(p1, l)*ply_get_coef(p2, k-l));
            }
        ply_set_coef(prod_poly, k, sum_k);
    }

    return prod_poly;
}

// analysis
//********************
Polynomial *ply_differentiate(Polynomial *poly, int n) {
    int deg = poly->deg;
    if (deg<n) {
        Polynomial *deriv = ply_create_poly(0);
        ply_set_coef(deriv, 0, 0.0);
        return deriv;
    }
    else {
        int dn_deg = deg-n;
        double dn_coefs[dn_deg+1];
        int i;
        for (i=0; i<=dn_deg; i++) {
            dn_coefs[i] = cnt_factorial(n+i, i+1)*ply_get_coef(poly, n+i);
        }

        while (dn_deg>=0) {
            if (dn_coefs[dn_deg]!=0)
                break;
            if (dn_deg==0)
                break;
            dn_deg = dn_deg-1;
        }

        Polynomial *deriv = ply_create_poly(dn_deg);
        for (i=0; i<=dn_deg; i++) {
            double coef = dn_coefs[i];
            ply_set_coef(deriv, i, coef);
        }

        return deriv;
    }
}

// families of polynomials

// Legendre (Rodriguez)
//***********************8
Polynomial *ply_legendre(int n) {
    Polynomial *p = ply_create_poly(2*n);
    int k;
    for (k=0; k<=2*n; k++) {
        if (k%2==0) {
            int exp = (n-k/2)%2;
            double coef = (1.0/pow(2.0, n))*(1.0/cnt_factorial(n, 1))*pow(-1.0, exp)*cnt_combination(n, k/2);
            ply_set_coef(p, k, coef);
        }
        else if (k%2==1) {
            ply_set_coef(p, k, 0.0);
        }
    }

    Polynomial *q = ply_differentiate(p, n);
    ply_delete_poly(p);

    return q;
}
