#pragma once
#include "MatrixCalculator.h"
#include "..\..\aquaUtils\FileUtils.h"
#include "DirectoryUtils.h"

void _MatrixWriteToFile(Matrix* out, string_t filename) {
    
    FILE* f;
    openFileW_s(&f, filename);
    if (f == 0) panic("I/O Error!");
    StringV sv; InitStringV(&sv);
    for (int i = 0; i < out->h; i++) {
        StringBuilder sb; InitStringBuilder(&sb, "");
        for (int j = 0; j < out->w; j++) {
            string_t tmp = SUS_format1024("%lf ", out->matrix[i][j]);
            sb.add(&sb, tmp);
            free(tmp);
        }
        sb.trim(&sb);
        sv.put(&sv, sb.buildAndDispose(&sb));
    }
    writeAllLines_s(f, &sv);
    closeFile(f);

}

void _MatrixDisplayResult(_MC_F_PROTOTYPE_, int func_id) {

    system("cls");
    printf("\n-=- Result -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
    Bool status = True;
    if (func_id < 3) {
        string fmt = SUS_format1024("# %c # = #", __map_k[func_id]);
        status = MatrixSmartPrint(fmt, 3, A, B, out);
    }
    if(func_id == 3) status = MatrixSmartPrint("# --[t]--> #", 2, A, out);
    if (func_id == 4)
    {
        string fmt = SUS_format1024("  det # = %lf", out->matrix[0][0]);
        status = MatrixSmartPrint(fmt, 1, A);
    }
    if (status == False) {
        printf(
            "\n\nCan't display result, result matrix will be saved to ..\\matrices\\out.txt\n\n"
        );
        _MatrixWriteToFile(out, getPathInDirectory("matrices", "out.txt"));
        system("pause");
    }
}

Bool _MatrixDisplayError(string_t msg) {
    system("cls");
    printf("\n\tError:\n\n\t  %s\n\n", msg);
    system("pause");
    return True;
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
        int wsize = 0;
        for (int j = 0; j < tmp.size; j++) {
            double tmp2 = 0;
            if (strstr(tmp.ptr[j], "n") != 0) return; // NOT A NUMBER
            if (SUS_getStringLength(tmp.ptr[j]) > 24) return; // MAX 10^24
            int status = sscanf_s(tmp.ptr[j], "%lf", &tmp2);
            if (status == 0) return;
            putToDoubleArray(&temp, &wsize, tmp2);
        }
        pushToBucket(&tmp_matrix, &out->h, temp);
        tmp.clear(&tmp);
    }
    out->matrix = (double**)tmp_matrix;
    out->w = first_size;
    out->__notnull__ = 1;
    sv.clear(&sv);
    closeFile(f);
}