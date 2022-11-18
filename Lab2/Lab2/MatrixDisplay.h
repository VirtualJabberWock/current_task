#pragma once
#include "MatrixCalculator.h"

const char* ___chr(char c) {
    char* t = (char*) initArray(2, sizeof(char));
    t[0] = c;
    t[1] = '\0';
    return t;
}

void _MatrixDisplayResult(_MC_F_PROTOTYPE_, int func_id) {
    if (func_id < 3) {
        string fmt = SUS_format1024("# %c # = #", __map_k[func_id]);
        MatrixSmartPrint(fmt, 3, A, B, out);
    }
    else {
        if(func_id == 3)
            MatrixSmartPrint("# --[t]--> #", 2, A, out);
        else
        {
            string fmt = SUS_format1024("det # = %lf", out->matrix[0][0]);
            MatrixSmartPrint(fmt, 1, A);
        }
    }
}