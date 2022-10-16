#include <stdio.h>
#include "DynamicList.h"
#include "Storage.h"
#include "StringUtils.h"

int __handle__() {
	
}

// TODO EVERY PUT FOR EVERY FUNC

Storage Storage_New()
{
	Storage self;
	//DATA
	self.__notnull__ = True;
	//

	IntV intV;
	intV.size = 0; intV.ptr = initList(0, 4);
	self._data32 = intV;
	LongV longV;
	longV.size = 0; longV.ptr = initList(0, 8);
	self._data64 = longV;
	DoubleV dV;
	dV.size = 0; dV.ptr = initList(0, 8);
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
	putToIntList(&(self->_data32.ptr), &(self->_data32.size), value);
}

void Storage_PutLong(__self, Long value)
{
	putTo64List(&(self->_data64.ptr), &(self->_data64.size), value);
}

void Storage_PutString(__self, string value)
{
	string a = str_copy(value);
	pushToBucket(&(self->_dataSB.ptr), &(self->_dataSB.size), a);
}

void Storage_PutDouble(__self, double value)
{
	putToDoubleList(&(self->_dataDV.ptr), &(self->_dataDV.size), value);
}    

// CLEAR

void Storage_ClearInt(__self) { _Storage_ClearData(self, _Type_Integer); }
void Storage_ClearLong(__self) { _Storage_ClearData(self, _Type_Long); }
void Storage_ClearString(__self) { _Storage_ClearData(self, _Type_String); }
void Storage_ClearDouble(__self) { _Storage_ClearData(self, _Type_Double); }

void _Storage_ClearData(__self, int type) {
	if (type == _Type_Integer) {
		self->_data32.ptr = (int* )_Storage_FP(self->_data32.ptr, sizeof(int));
		self->_data32.size = 0;
	}
	if (type == _Type_Long) {
		self->_data64.ptr = (__int64*)_Storage_FP(self->_data64.ptr, 8);
		self->_data64.size = 0;
	}
	if (type == _Type_Double) {
		self->_dataDV.ptr = (double*)_Storage_FP(self->_dataDV.ptr, sizeof(double));
		self->_dataDV.size = 0;
	}
	if (type == _Type_String) {
		freeBucket(self->_dataSB.ptr, self->_dataSB.size);
		self->_dataSB.ptr = initBucket(0);
		self->_dataSB.size = 0;
	}
}
void* _Storage_FP(void* ptr, int b_size) // free pointer
{
	if (ptr != 0) {
		printf("%p, %d\n", ptr, b_size);
		free(ptr);
	}
	return initList(1, b_size);
}
