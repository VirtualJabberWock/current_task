#include "Matrices.h"

void InitMatrix(Matrix* m, int w, int h)
{
    m->__notnull__ = true;
    m->hsize = h;
    m->wsize = w;
    m->matrix = (int**)initArray(h, sizeof(void*));
    for (int i = 0; i < h; i++) {
        m->matrix[i] = (int*)initArray(w, sizeof(int));
    }
}

errno_t MatrixAddition(Matrix* l, Matrix* r, Matrix* out)
{
    if (l->__notnull__ == false) panic_NPE();
    if (r->__notnull__ == false) panic_NPE();
    if (r->hsize != l->hsize) return MATRIX_ERR_DIFFRENT_SIZES;
    if (r->wsize != l->wsize) return MATRIX_ERR_DIFFRENT_SIZES;
    if (out->__notnull__ == false) {
        InitMatrix(out, r->hsize, r->wsize);
    }
    else {
        if (r->wsize != out->wsize) return MATRIX_ERR_DIFFRENT_SIZES;
        if (r->hsize != out->hsize) return MATRIX_ERR_DIFFRENT_SIZES;
    }

    for (int i = 0; i < r->hsize; i++) {
        for (int j = 0; j < r->wsize; j++) {
            out->matrix[i][j] = r->matrix[i][j] + l->matrix[i][j];
        }
    }

    return 0;
}

/*
bucket should be empty;
*/
void MatrixToString(Matrix* m, StringMatrix* bucket)
{
    if (m->__notnull__ == false) panic_NPE();
    if (bucket->__notnull__ == false) panic_NPE();
    if (bucket->size != 0) panic("Matrices.MatrixToString() :: Bucket should be empty!");
    for (int i = 0; i < m->hsize; i++) {
        StringV line;
        InitStringV(&line);
        for (int j = 0; j < m->wsize; j++) {
            const char* buffer = initArray(20, sizeof(char));
            itoa(m->matrix[i][j], buffer, 10);
            line.put(&line, buffer);
            free(buffer);
;        }
        bucket->put(bucket, &line);
    }
}
