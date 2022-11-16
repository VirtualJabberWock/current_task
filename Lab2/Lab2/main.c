#include <stdio.h>
#include "ExtendedTypes.h"
#include "Matrices.h"
#include <stdlib.h>
#include "MatrixCalculator.h"
#include "MatrixDisplay.h"

int main() {
    Matrix m;
    Matrix m2;
    InitMatrix(&m, 3, 3);
    InitMatrix(&m2, 3, 3);
    double A[3][3] = { {2,4,8} ,{2,4,8}, {2,4,8} };
    double B[3][3] = { {1,0,0} ,{0,1,0}, {0,0,1} }; 
    MatrixFrom3x3(&m, A);
    MatrixFrom3x3(&m2, B);
    Matrix out;
    InitMatrix(&out, 3, 3);
    handleMatrixOperation(&m, &m2, &out, 'd');
    
}