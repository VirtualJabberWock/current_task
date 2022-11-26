#include <stdio.h>
#include "ArrayUtils.h"
#include "AquaTypes.h"
#include "StringUtils.h"

Storage NewStorage()
{
	Storage self;
	//DATA
	self.__notnull__ = True;
	//

	IntV intV;
	intV.size = 0; intV.ptr = initArray(0, 4);
	self._data32 = intV;
	LongV longV;
	longV.size = 0; longV.ptr = initArray(0, 8);
	self._data64 = longV;
	DoubleV dV;
	dV.size = 0; dV.ptr = initArray(0, 8);
	self._dataDV = dV;
	StringV sV;
	sV.size = 0; sV.ptr = initBucket(0);
	self._dataSB = sV;

	self.putInt = Storage_PutInt;
	self.putLong = Storage_PutLong;
	self.putString = Storage_PutString;
	self.putDouble = Storage_PutDouble;

	self.clearInt = Storage_ClearInt;
	self.clearLong = Storage_ClearLong;
	self.clearString = Storage_ClearString;
	self.clearDouble = Storage_ClearDouble;

	self.free = Storage_Free;

	return self;
}

StringVP NewStringV()
{
	StringV sv;
	InitStringV(&sv);
	return &sv;
}

IntVP NewIntV()
{
	IntV iv;
	InitIntV(&iv);
	return &iv;
}

void InitStringV(StringV* v)
{
	v->__notnull__ = 1;
	v->put = _Default_Vector_PutString;
	v->clear = _Default_Vector_ClearString;
	v->size = 0;
	v->ptr = initBucket(0);
}

void InitIntV(IntV* v)
{
	v->__notnull__ = 1;
	v->put = _Default_Vector_PutInt;
	v->clear = _Default_Vector_ClearInt;
	v->size = 0;
	v->ptr = initArray(0, sizeof(int));
}

void InitLongV(LongV* v)
{
	v->__notnull__ = 1;
	v->put = _Default_Vector_PutLong;
	v->clear = _Default_Vector_ClearLong;
	v->size = 0;
	v->ptr = initArray(0, sizeof(__int64));
}

void InitDoubleV(DoubleV* v)
{
	v->__notnull__ = 1;
	v->put = _Default_Vector_PutDouble;
	v->clear = _Default_Vector_ClearDouble;
	v->size = 0;
	v->ptr = initArray(0, sizeof(double));
}

void InitStringBuilder(StringBuilder* builder, string_t base_nt)
{
	builder->buffer = initArray(0, sizeof(char));
	builder->b_size = 0;
	if (SUS_getStringLength(base_nt) > 0) {
		int j = 0;
		while (base_nt[j] != '\0') {
			pushToCharArray(&(builder->buffer), &builder->b_size, base_nt[j]);
			j++;
		}
	}
	builder->add = _Default_SB_Append;
	builder->trim = _Default_SB_Trim;
	builder->build = _Default_SB_Build;
	builder->buildAndDispose = _Default_SB_BuildAndDispose;
	builder->__notnull__ = 1;
}

void Storage_Free(__self) {

	if (self == 0) return;
	if (!self->__notnull__) return;
	void* ptr0 = (*self)._data32.ptr;
	void* ptr1 = (*self)._data64.ptr;
	void* ptr2 = (*self)._dataDV.ptr;
	void* ptr3 = (*self)._dataSB.ptr;

	if ((*self)._data32.ptr != 0) free(ptr0);
	if ((*self)._dataDV.ptr != 0) free(ptr2);
	if ((*self)._data64.ptr != 0) free(ptr1);
	if ((*self)._dataSB.ptr != 0)
		freeBucket(ptr3, (*self)._dataSB.size);
	(*self).__notnull__ = False;
	
	
}

// PUT

void Storage_PutInt(__self, int value)
{
	putToIntArray(&(self->_data32.ptr), &(self->_data32.size), value);
}

void Storage_PutLong(__self, __int64 value)
{
	putTo64Array(&(self->_data64.ptr), &(self->_data64.size), value);
}

void Storage_PutString(__self, string_t value)
{
	string_t a = SUS_str_copy(value);
	pushToBucket(&(self->_dataSB.ptr), &(self->_dataSB.size), a);
}

void Storage_PutDouble(__self, double value)
{
	putToDoubleArray(&(self->_dataDV.ptr), &(self->_dataDV.size), value);
}

//

void _Default_Vector_PutInt(IntV* v, int value)
{
	putToIntArray(&(v->ptr), &(v->size), value);
}

void _Default_Vector_PutLong(LongV* v, __int64 value)
{
	putTo64Array(&(v->ptr), &(v->size), value);
}

void _Default_Vector_PutString(StringV* v, string_t value)
{
	string_t a = SUS_str_copy(value);
	pushToBucket(&(v->ptr), &(v->size), a);
}

void _Default_Vector_PutDouble(DoubleV* v, double value)
{
	putToDoubleArray(&(v->ptr), &(v->size), value);
}

// CLEAR

void Storage_ClearInt(__self) { _Default_Vector_ClearInt(&(self->_data32)); }
void Storage_ClearLong(__self) { _Default_Vector_ClearInt(&(self->_data64)); }
void Storage_ClearString(__self) { _Default_Vector_ClearInt(&(self->_dataSB)); }
void Storage_ClearDouble(__self) { _Default_Vector_ClearInt(&(self->_dataDV)); }

void _Default_Vector_ClearInt(IntV* v)
{
	if (v->ptr != 0) free(v->ptr);
	v->ptr = (int*)initArray(0, sizeof(int));
	v->size = 0;
}
void _Default_Vector_ClearLong(LongV* v)
{
	if (v->ptr != 0) free(v->ptr);
	v->ptr = (__int64*)initArray(0, sizeof(__int64));
	v->size = 0;
}
void _Default_Vector_ClearDouble(DoubleV* v)
{
	if (v->ptr != 0) free(v->ptr);
	v->ptr = (double*)initArray(0, sizeof(double));
	v->size = 0;
}
void _Default_Vector_ClearString(StringV* v)
{
	freeBucket(v->ptr, v->size);
	v->ptr = initBucket(0);
	v->size = 0;
}

StringBuilder* _Default_SB_Append(StringBuilder* sb, string_t str) {
	if (sb->buffer == 0)
		panic_NPE(_Default_SB_Append, "<char*> sb->buffer");
	int i = 0;
	while (str[i] != '\0') {
		pushToCharArray(&(sb->buffer), &(sb->b_size), str[i]);
		i++;
	}
	return sb;
}

void _Default_SB_Trim(StringBuilder* sb) {
	if (sb->buffer == 0)
		panic_NPE(_Default_SB_Trim, "<char*> sb->buffer");
	sb->buffer = SUS_trim(sb->buffer);
}

string_t _Default_SB_Build(StringBuilder* sb) {
	if (sb->buffer == 0)
		panic_NPE(_Default_SB_Build, "<char*> sb->buffer");
	return SUS_str_lock(sb->buffer, sb->b_size);
}

string_t _Default_SB_BuildAndDispose(StringBuilder* sb) {
	if (sb->buffer == 0)
		panic_NPE(_Default_SB_BuildAndDispose, "<char*> sb->buffer");
	string_t r = buildString(sb->buffer, sb->b_size);
	sb->buffer = initArray(0, sizeof(char));
	sb->b_size = 0;
	return r;
}