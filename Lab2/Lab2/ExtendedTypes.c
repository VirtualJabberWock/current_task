#include "ExtendedTypes.h"

void InitStringMatrix(StringMatrix* str_m)
{
	str_m->__notnull__ = true;
	str_m->size = 0;
    str_m->ptr = (StringV**)initBucket(0);
    str_m->put = Default_StringMatrix_Put;
    str_m->clear = Default_StringMatrix_Clear;
    str_m->get = Default_StringMatrix_Get;
}

void Default_StringMatrix_Put(StringMatrix* self, StringV* str_v)
{
    if (self->__notnull__ == false) panic_NPE();
    if (str_v->__notnull__ == false) panic_NPE();
    pushToBucket(&self->ptr, self->size, str_v);

}

void Default_StringMatrix_Clear(StringMatrix* self)
{
    if (self->__notnull__ == false) panic_NPE();
    if (self->ptr != 0) {
        freeBucket(self->ptr, self->size);
        self->ptr = initBucket(0);
        self->size = 0;
    }
}

void Default_StringMatrix_Get(StringMatrix* self, int i, int j)
{
    if (self->__notnull__ == false) panic_NPE();
    return self->ptr[i]->ptr[j];
}
