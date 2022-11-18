#pragma once
#include "MatrixCalculator.h"
#include "..\..\aquaUtils\FileUtils.h"

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

/*
* TODO :: Test this
@param [Nullable] init_out, filename
*/
void ScanMatrixFromFile(Matrix *out, string_t filename) {

    out->__notnull__ = 0;
    out->w = 0;
    out->h = 0;
    void** tmp_matrix = (void**)initArray(0, sizeof(void*));
    FILE *f;
    openFile_s(&f, filename);
    if (f == 0) panic("I/O Error!");
    StringV sv; InitStringV(&sv);
    readAllLines_s(f, &sv);
    if (sv.size == 0) return;
    int first_size = -1;
    for (int i = 0; i < sv.size; i++) {
        StringV tmp; InitStringV(&tmp);
        tmp.ptr = SUS_split(SUS_trim(sv.ptr[i]), ' ', &tmp.size);
        if (first_size == -1) first_size = tmp.size;
        if (tmp.size == 0) return;
        if (tmp.size != first_size) return;
        double* temp = (double*)initArray(0, sizeof(double));
        for (int j = 0; j < tmp.size; j++) {
            double tmp2 = 0;
            int status = sscanf(tmp.ptr[j], "&lf", &tmp2);
            if (status == 0) return;
            putToDoubleArray(&temp, &out->w, tmp2);
        }
        pushToBucket(&tmp_matrix, &out->h, temp);
        tmp.clear(&tmp);
    }
    out->w = first_size;
    out->__notnull__ = 1;
    closeFile(f);
}