#pragma once

#include "ArrayUtils.h"

#define Byte char
#define Bool char

#define True 1
#define False 0

#define _Type_Integer 0x01
#define _Type_Long    0x02
#define _Type_Double  0x03
#define _Type_String  0x04

#define __self Storage *self
#define __self__ struct StorageS* self

// ~~~~ INTEFACES :

typedef struct tagStringBuilder {
	char* buffer;
	int b_size;
	// hmmm why not "append"??? it maybe right name, but... you know... korotkiy kod tipo
	struct tagStringBuilder* (*add) (struct tagStringBuilder* self, string str_nt);
	void (*trim) (struct tagStringBuilder* self);
	//void (*replaceAll) (struct tagStringBuilder* self, string pattern, string to); //TODO!!!
	string (*build) (struct tagStringBuilder* self);
	string (*buildAndDispose) (struct tagStringBuilder* self);
	Bool __notnull__;
} StringBuilder;

typedef struct StringVS {
	string* ptr;
	int size;
	/*Put the COPY of string to Vector*/
	void (*put) (struct StringVS* self, string value);
	void (*clear)(struct StringVS* self);
	Bool __notnull__; // (self == null) ? 0 : 1
} StringV, *StringVP;


typedef struct IntVS {
	int* ptr;
	int size;
	void (*put) (struct IntVS* self, int value);
	void (*clear)(struct IntVS* self);
	Bool __notnull__; // (self == null) ? 0 : 1
} IntV, *IntVP;

typedef struct LongVS {
	__int64* ptr;
	int size;
	void (*put) (struct LongVS* self, __int64 value);
	void (*clear)(struct LongVS* self);
	Bool __notnull__; // (self == null) ? 0 : 1
} LongV;

typedef struct DoubleVS {
	double* ptr;
	int size;
	void (*put) (struct DoubleVS* self, double value);
	void (*clear)(struct DoubleVS* self);
	Bool __notnull__; // (self == null) ? 0 : 1
} DoubleV;

#define isNull(obj) (obj.__notnull__ == False)
#define isNullP(obj) (obj->__notnull__ == False)

typedef struct StorageS {

	void (*putInt)    (__self__, int value);
	void (*putLong)   (__self__, __int64 value);
	void (*putDouble) (__self__, double value);
	void (*putString) (__self__, string value);

	void (*clearInt)    (__self__);
	void (*clearLong)   (__self__);
	void (*clearDouble) (__self__);
	void (*clearString) (__self__);

	void (*free)(__self__);
	Bool __notnull__; // (self == null) ? 0 : 1
	
	IntV    _data32; //store int32
	LongV   _data64; //store int64
	DoubleV _dataDV; //store double
	StringV _dataSB; //store strings


} Storage;

// STORAGE DEFAULT

Storage NewStorage();
StringVP NewStringV();
IntVP NewIntV();

void InitStringV(StringV* v);
void InitIntV(IntV* v);
void InitLongV(LongV* v);
void InitDoubleV(DoubleV* v);

void InitStringBuilder(StringBuilder *builder, string base_nt);

void Storage_Free(__self);

// INTERFACES DEFAULTS

void Storage_PutInt(__self, int value);
void Storage_PutLong(__self, __int64 value);
void Storage_PutString(__self, string value);
void Storage_PutDouble(__self, double value);

void Storage_ClearInt(__self);
void Storage_ClearLong(__self);
void Storage_ClearString(__self);
void Storage_ClearDouble(__self);

void _Default_Vector_PutInt(IntV* v, int value);
void _Default_Vector_PutLong(LongV* v, __int64 value);
void _Default_Vector_PutString(StringV* v, string value);
void _Default_Vector_PutDouble(DoubleV* v, double value);

void _Default_Vector_ClearInt(IntV* v);
void _Default_Vector_ClearLong(LongV* v);
void _Default_Vector_ClearString(StringV* v);
void _Default_Vector_ClearDouble(DoubleV* v);

StringBuilder* _Default_SB_Append(StringBuilder* sb, string str);
void _Default_SB_Trim(StringBuilder* sb);
string _Default_SB_Build(StringBuilder* sb);
string _Default_SB_BuildAndDispose(StringBuilder* sb);

