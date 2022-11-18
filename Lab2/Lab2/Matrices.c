#include "Matrices.h"
#include <stdarg.h>
#include <Windows.h>
#include "BareissAlgorithm.h"

static const __int64 NAN_VALUE = 0xff'f8'00'00'00'00'00'00;

void InitMatrix(Matrix* m, int w, int h)
{
    m->__notnull__ = true;
    m->h = h;
    m->w = w;
    if (m->matrix != 0) free(m->matrix);
    m->matrix = (double**)initArray(h, sizeof(void*));
    for (int i = 0; i < h; i++) {
        m->matrix[i] = (double*)initArray(w, sizeof(double));
    }
}

void MatrixFrom3x3(Matrix* m, double A[3][3])
{
    if (m->h != 3) panic("Can't create 3x3 matrix given nxm, where n != 3");
    if (m->w != 3) panic("Can't create 3x3 matrix given nxm, where m != 3");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m->matrix[i][j] = A[i][j];
        }
    }
}

void MatrixFrom5x5(Matrix* m, double A[5][5]) {
    if (m->h != 5) panic("Can't create 5x5 matrix given nxm, where n != 5");
    if (m->w != 5) panic("Can't create 5x5 matrix given nxm, where m != 5");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m->matrix[i][j] = A[i][j];
        }
    }
}

errno_t MatrixAddition(Matrix* l, Matrix* r, Matrix* out)
{
    if (l->__notnull__ == false) return MATRIX_ERR_LEFT_REQUIRED;
    if (r->__notnull__ == false) return MATRIX_ERR_RIGHT_REQUIRED;
    if (out->__notnull__ == 0) panic_NPE();

    if (!_MatrixCheckForSameSize(r, l)) return MATRIX_ERR_DIFFRENT_SIZES;
    if (!_MatrixCheckForSameSize(r, out)) return MATRIX_ERR_INVALID_OUT;

    for (int i = 0; i < r->h; i++) {
        for (int j = 0; j < r->w; j++) {
            out->matrix[i][j] = r->matrix[i][j] + l->matrix[i][j];
        }
    }
    return 0;
}

errno_t MatrixSubstract(Matrix* l, Matrix* r, Matrix* out)
{
    if (out->__notnull__ == False) panic_NPE();
    if (r->__notnull__ == False) return MATRIX_ERR_RIGHT_REQUIRED;
    if (!_MatrixCheckForSameSize(r, out)) return MATRIX_ERR_INVALID_OUT;

    int s = MatrixCopy(r, out);
    if (s != 0) return s;
    MatrixFactor(out, -1, out);
    return MatrixAddition(out, l, out);
}

double MatrixGetDeterminant(Matrix* A)
{
    Matrix temp;
    double bridge = 0;
    if (A->h != A->w) {
        if (sizeof(double) != 8) panic("[x86] Nope!");
        memcpy(&bridge, &NAN_VALUE, sizeof(double));
        return bridge;
    }
    InitMatrix(&temp, A->w, A->h);
    MatrixCopy(A, &temp);
    //O(n^3) but there is no particular problem with rounding !!!
    bridge = getDeterminantBareiss(&temp);
    //... native double (architecture x86) may be ? ff f0 00 00 00 00 00 00
    return bridge;
}

errno_t MatrixFactor(Matrix* l, double alpha, Matrix* out)
{
    if(l->__notnull__ == 0) return MATRIX_ERR_LEFT_REQUIRED;
    for (int i = 0; i < l->h; i++) {
        for (int j = 0; j < l->w; j++) {
            out->matrix[i][j] = l->matrix[i][j] * alpha;
        }
    }
    return 0;
}

errno_t MatrixMultiply(Matrix* l, Matrix* r, Matrix* out)
{
    if (l->__notnull__ == false) return MATRIX_ERR_LEFT_REQUIRED;
    if (r->__notnull__ == false) return MATRIX_ERR_RIGHT_REQUIRED;
    if (out->__notnull__ == 0) panic_NPE();

    if (l->w != r->h) return MATRIX_ERR_INVALID_MULTIPLY;   
    if (l->h != out->h) return MATRIX_ERR_INVALID_OUT;
    if (r->w != out->w) return MATRIX_ERR_INVALID_OUT;

    for (int i = 0; i < out->h; i++) {
        for (int j = 0; j < out->w; j++) {
            double c = 0;
            for (int inner = 0; inner < l->h; inner++) {
                c += r->matrix[i][inner] * l->matrix[inner][j];
            }
            out->matrix[i][j] = c;
        }
    }

    return 0;
}

/* @param NP - NULL POINTER (0) */
errno_t MatrixTranspose(Matrix* A, Matrix* NP, Matrix* out)
{
    if(A->__notnull__ == False) return MATRIX_ERR_LEFT_REQUIRED;
    for (int i = 0; i < A->h; i++) {
        for (int j = 0; j < A->w; j++) {
            out->matrix[i][j] = A->matrix[j][i];
        }
    }
    return 0;
}

/* @param NP - NULL POINTER (0) */
errno_t MatrixDeterminate(Matrix* A, Matrix* NP, Matrix* out)
{
    if (A->__notnull__ == False) return MATRIX_ERR_LEFT_REQUIRED;
    if (A->h != A->w) return MATRIX_ERR_NOT_SQUARE;
    out->matrix[0][0] = MatrixGetDeterminant(A);
    return 0;
}

errno_t MatrixCopy(Matrix* from, Matrix* to)
{
    if (to->__notnull__ == false) panic_NPE();
    if (from->__notnull__ == false) panic_NPE();
    if (!_MatrixCheckForSameSize(to, from)) return MATRIX_ERR_INVALID_COPY;

    for (int i = 0; i < to->h; i++) {
        for (int j = 0; j < to->w; j++) {
            to->matrix[i][j] = from->matrix[i][j];
        }
    }
    return 0;
}


error_msg_t MatrixErrorHandler(int status)
{
    if (status == 0) return NULL;

    switch (status) {
    
    case MATRIX_ERR_DIFFRENT_SIZES:
        return "Matrices :: Invalid operation! (Matrices have diffrent sizes)";
    case MATRIX_ERR_INVALID_OUT:
        return "Matrices :: Invalid operation! (Output matrix should valid size)";
    case MATRIX_ERR_INVALID_MULTIPLY:
        return "Matrices :: Invalid operation! (For multiply, expected sizes: (nxm) * (mxq)";
    case MATRIX_ERR_INVALID_COPY:
        return "Matrices :: Invalid operation! (Can't copy matrix to matrix with diffrent size)";
    case MATRIX_ERR_NOT_SQUARE:
        return "Matrices :: Invalid operation! (Matrix should have square size)";
    case MATRIX_ERR_LEFT_REQUIRED:
        return "Matrices :: Operation require left matrix, which was NULL!";
    case MATRIX_ERR_RIGHT_REQUIRED:
        return "Matrices :: Operation require right matrix, which was NULL!";
    }

    return "Matrices :: Unknown error";
}

Bool _MatrixCheckForSameSize(Matrix* A, Matrix* B)
{
    if (A->h != B->h) return False;
    if (A->w != B->w) return False;
    return True;
}

/*
* only for square matrices [Note: a(ij) < 100]
* # - for format
*/
Bool MatrixSmartPrint(string format, int c, ...) {
    int i = 0;
    StringV sv; InitStringV(&sv);
    sv.ptr = SUS_split(format, '#', &sv.size);
    Matrix* arr = (Matrix*)initArray(c, sizeof(Matrix));
    Matrix* tmp;
    int last_size = -1;
    va_list ap;
    va_start(ap, c); // 
    for (int j = 0; j < c; j++) {
        tmp = va_arg(ap, Matrix*);
        arr[j].__notnull__ = tmp->__notnull__;
        arr[j].h = tmp->h;
        arr[j].w = tmp->w;
        if (tmp->h != tmp->w)
            return (!printf("MatrixSmartPrint :: Can't DISPLAY not square matrix!"));
        arr[j].matrix = tmp->matrix;
        if (last_size == -1) {
            last_size = arr[j].h;
            continue;
        }
        if (last_size != arr[j].h)
            return (!printf("MatrixSmartPrint :: Every matrix should have same size!"));
    }
    for (int j = 0; j < last_size; j++) {
        for (int k = 0; k < c + 1; k++) {
            if (j != last_size / 2) {
                for (int i = 0; i < SUS_getStringLength(sv.ptr[k]); i++) printf(" ");
            }
            else {
                printf("%s", sv.ptr[k]);
            }
            printf(" ");
            for (int i = 0; i < last_size; i++) {
                if(k != c) printf("%2d  ", (int)arr[k].matrix[j][i]);
            }
        }
        printf("\n");
    }
    va_end(ap);
    return True;
}
