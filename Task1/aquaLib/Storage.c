#include <stdio.h>
#include "Storage.h"
#include "DynamicList.h"

int __handle__() {
	
}

// TODO EVERY PUT FOR EVERY FUNC

Storage Storage_New()
{
	Storage self;
	//DATA
	self.__notnull__ = True;
	self._dataBV = initList(0, sizeof(char));
	//

	self._data32.ptr = 0;
	self._data64.ptr = 0;
	self._dataDV.ptr = 0;
	self._dataSB.ptr = 0;
	Storage_ClearInt(&self);
	Storage_ClearDouble(&self);
	Storage_ClearLong(&self);
	Storage_ClearString(&self);

	//

	self.putInt = Storage_PutInt;
	self.putLong = Storage_PutLong;
	self.putString = Storage_PutString;
	self.putDouble = Storage_PutDouble;
	self.free = Storage_Free;

	return self;
}

void Storage_Free(__self) {
	if (self->_data32.ptr != 0) free(self->_data32.ptr);
	if (self->_data64.ptr != 0) free(self->_data64.ptr);
	if (self->_dataDV.ptr != 0) free(self->_dataDV.ptr);
	if (self->_dataBV != 0) free(self->_dataBV);
	if (self->_dataSB.ptr != 0)
		freeBucket(self->_dataSB.ptr, self->_dataSB.size);
	self->__notnull__ = False;
}

// PUT

void Storage_PutInt(__self, int value)
{
	putToIntList(&self->_data32.ptr, &self->_data32.size, value);
}

void Storage_PutLong(__self, Long value)
{
	putTo64List(&self->_data64.ptr, &self->_data64.size, value);
}

void Storage_PutString(__self, string value)
{
	pushToBucket(&self->_dataSB.ptr, &self->_dataSB.size, value);
}

void Storage_PutDouble(__self, double value)
{
	putToDoubleList(&self->_dataDV.ptr, &self->_dataDV.size, value);
}    

// CLEAR

void Storage_ClearInt(__self) { _Storage_ClearData(self, _Type_Integer); }
void Storage_ClearLong(__self) { _Storage_ClearData(self, _Type_Long); }
void Storage_ClearString(__self) { _Storage_ClearData(self, _Type_String); }
void Storage_ClearDouble(__self) { _Storage_ClearData(self, _Type_Double); }

void _Storage_ClearData(__self, int type) {
	if (type == _Type_Integer) {
		self->_data32.ptr = _Storage_FP(self->_data32.ptr, sizeof(int));
		self->_data32.size = 0;
	}
	if (type == _Type_Long) {
		self->_data64.ptr = _Storage_FP(self->_data64.ptr, 8);
		self->_data64.size = 0;
	}
	if (type == _Type_Double) {
		self->_dataDV.ptr = _Storage_FP(self->_dataDV.ptr, sizeof(double));
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
	if (ptr != 0) free(ptr);
	return initList(0, b_size);
}
