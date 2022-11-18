#pragma once
#include "Matrices.h"

#define OPERATIONS_COUNT 5
#define _MC_F_PROTOTYPE_ Matrix * A, Matrix * B, Matrix * out

char __map_k[OPERATIONS_COUNT] = {
    '+', '-', '*', 't', 'd'
};

void* __map_v[OPERATIONS_COUNT] = {
    MatrixAddition,
    MatrixSubstract,
    MatrixMultiply,
    MatrixTranspose,
    MatrixDeterminate
};

#include "MatrixIO.h"

/*
@param
    [optional] for 't' or 'd', would better be, if B = NULL 

@return
    False - if operation doesn't exist
*/
Bool handleMatrixOperation(Matrix* A, Matrix* B, Matrix* out, char o) {

    int func_id = -1;
    for (int i = 0; i < OPERATIONS_COUNT; i++) if (__map_k[i] == o) func_id = i;
    if (func_id == -1) return False; //Not found
    errno_t s = ((errno_t (*)(_MC_F_PROTOTYPE_)) __map_v[func_id])(A, B, out);
    MatrixErrorHandler(s);
    _MatrixDisplayResult(A, B, out, func_id);
    return True;
}

