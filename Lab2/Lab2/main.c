#include <stdio.h>
#include "ExtendedTypes.h"
#include "Matrices.h"
#include <stdlib.h>
#include "MatrixCalculator.h"
#include "MatrixDisplay.h"

int main() {
    Matrix m;
    Matrix m2;
    InitMatrix(&m, 5, 5);
    InitMatrix(&m2, 5, 5);
    double A[5][5] = { {9,4,8,6,7} ,{2,5,9,7,8}, {3,6,9,6,9}, {4,7,1,6,10}, {5,8,8,5,1} };
    double B[5][5] = { {1,0,0} ,{0,1,0}, {0,0,1} }; 
    MatrixFrom5x5(&m, A);
    MatrixFrom5x5(&m2, B);
    Matrix out;
    InitMatrix(&out, 5, 5);
    handleMatrixOperation(&m, &m2, &out, 'd');
    
}