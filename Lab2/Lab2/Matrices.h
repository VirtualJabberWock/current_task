#pragma once
#include "..\..\aquaUtils\pch.h";
#include "bool.h"
#include "ExtendedTypes.h"

#define MATRIX_ERR_DIFFRENT_SIZES

typedef struct tagMatrix {
    
    Bool __notnull__;
    int wsize;
    int hsize;
    int** matrix;

} Matrix;

void InitMatrix(Matrix* m, int w, int h);

errno_t MatrixAddition(Matrix* l, Matrix* r, Matrix* out);

void MatrixToString(Matrix* m, StringMatrix* bucket);