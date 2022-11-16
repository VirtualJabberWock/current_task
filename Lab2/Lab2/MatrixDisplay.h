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
        StringBuilder sb; InitStringBuilder(&sb, "");
        sb.add(&sb, "# ")
            ->add(&sb, ___chr(__map_k[func_id]))
            ->add(&sb, " # = #");
        MatrixSmartPrint(sb.buildAndDispose(&sb), 3, A, B, out);
    }
    else {
        if(func_id == 3)
            MatrixSmartPrint("# --[t]--> #", 2, A, out);
        else
        {
            Matrix temp; InitMatrix(&temp, 3, 3);
            temp.matrix[1][1] = out->matrix[0][0];
            MatrixSmartPrint("# FIX_THIS_PLEASE ", 2, A, temp);
            //todo it with own sprintf_s function
        }
    }
}