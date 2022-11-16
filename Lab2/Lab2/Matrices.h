#pragma once
#include "..\..\aquaUtils\pch.h";
#include "bool.h"
#include "ExtendedTypes.h"

#define MATRIX_ERR_DIFFRENT_SIZES 0x100
#define MATRIX_ERR_INVALID_OUT 0x101
#define MATRIX_ERR_INVALID_MULTIPLY 0x102
#define MATRIX_ERR_INVALID_COPY 0x103
#define MATRIX_ERR_NOT_SQUARE 0x104

typedef struct tagMatrix {
    
    Bool __notnull__;
    int w;
    int h;
    double** matrix;

} Matrix;

void InitMatrix(Matrix* m, int w, int h);

/*For debugging purposes*/
void MatrixFrom3x3(Matrix* m, double A[3][3]);

errno_t MatrixAddition(Matrix* l, Matrix* r, Matrix* out);
errno_t MatrixSubstract(Matrix* l, Matrix* r, Matrix* out);
errno_t MatrixMultiply(Matrix* l, Matrix* r, Matrix* out);
/* @param NP: NULL POINTER (0)*/
errno_t MatrixTranspose(Matrix* A, Matrix* NP, Matrix* out);
errno_t MatrixDeterminate(Matrix* A, Matrix* NP, Matrix* out);

double MatrixGetDeterminant(Matrix* A);

errno_t MatrixFactor(Matrix* l, double alpha, Matrix* out);
errno_t MatrixCopy(Matrix* from, Matrix* to);


void MatrixErrorHandler(int status);

/*1 - if matrices have same size*/
Bool _MatrixCheckForSameSize(Matrix* A, Matrix* B);

void MatrixSmartPrint(
    string format, int c, ...
);

