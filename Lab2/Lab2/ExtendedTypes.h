#pragma once
#include "bool.h"
#include "..\..\aquaUtils\StringUtils.h"
#include "..\..\aquaUtils\AquaTypes.h"

typedef struct tagStringMatrix {
    Bool __notnull__;
    StringV** ptr;
    int size;
    void (*put) (struct tagStringMatrix* self, StringV* str_v);
    void (*clear)(struct tagStringMatrix* self);
    string (*get)(struct tagStringMatrix* self, int i, int j);
    Bool __notnull__; // (self == null) ? 0 : 1
}
StringMatrix;

void InitStringMatrix(StringMatrix* str_m);

void Default_StringMatrix_Put(StringMatrix* self, StringV* str_v);
void Default_StringMatrix_Clear(StringMatrix* self);
void Default_StringMatrix_Get(StringMatrix* self, int i, int j);