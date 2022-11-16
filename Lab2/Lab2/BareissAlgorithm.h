#pragma once
#include "Matrices.h"

void swap(double* a, double* b) {
    double temp = *b;
    *b = *a;
    *a = temp;
}

/*
For [NxN] Matrix only
*/
double getDeterminantBareiss(Matrix* A) {

    int size = A->h;
    double sign = 1;

    for (int k = 0; k < size - 1; k++) {
        if (A->matrix[k][k] == 0) {
            int m = 0;
            for (m = k + 1; m < size; m++) {
                if (A->matrix[m][k] != 0) {
                    swap(A->matrix[m], A->matrix[k]);
                    sign = -sign;
                    break;
                }
            }
            if (m == size) {
                return 0;
            }
        }

        for (int i = k + 1; i < size; i++) {
            for (int j = k + 1; j < size; j++) {
                A->matrix[i][j] = A->matrix[k][k] * A->matrix[i][j] - A->matrix[i][k] * A->matrix[k][j];
                if (k != 0) {
                    A->matrix[i][j] /= A->matrix[k - 1][k - 1];
                }
            }
        }
    }
    return sign * A->matrix[size - 1][size - 1];
}