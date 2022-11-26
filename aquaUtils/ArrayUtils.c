#include "ArrayUtils.h"

void* initArray(int size, int b_size)
{
	return (void*)calloc(size, b_size);
}

void expandIntArray(int** list, int new_size) {
	int* tmp = (int*)realloc((void*)(*list), new_size * sizeof(int));
	if (tmp == NULL) panic("List::Memory allocation error!");
	else *list = tmp;
}

void copyIntArray(int* from, int* to, int begin, int end) {
	for (int i = 0; i < (end - begin) + 1; i++) {
		to[i] = from[i + begin];
	}
}

void putToIntArray(int** list, int* size, int num)
{
	expandCharArray(list, (*size) + 1);
	(*list)[(*size)] = num;
	*size = *size + 1;
}

void fillIntArray(int* list, int len, int value) {
	for (int i = 0; i < len; i++) {
		list[i] = value;
	}
}

void pushToCharArray(char** list, int* size, char chr) {
	expandCharArray(list, (*size) + 1);
	(*list)[(*size)] = chr;
	*size = *size + 1;
}

const char* buildString(char* string_list, int buffer_size) {
	char* buf0 = initArray(buffer_size + 1, sizeof(char));
	for (int i = 0; i < buffer_size; i++) buf0[i] = string_list[i];
	buf0[buffer_size] = '\0';
	if(string_list != 0) free(string_list); // Dispose
	string_list = 0;
	return buf0;
}

const char* buildLine(char* string_list, int buffer_size) {
	char* buf0 = initArray(buffer_size + 1, sizeof(char));
	int tmp = 0;
	for (int i = 0; i < buffer_size; i++) {
		if ((string_list[i] != '\n') && (string_list[i] != '\r')) {
			buf0[i] = string_list[i];
		}
		tmp++;
	}
	buf0[tmp] = '\0';
	if (string_list != 0) free(string_list); // Dispose
	string_list = 0;
	return buf0;
}

void expandCharArray(char** list, int new_size){
	void* address = (*list);
	if (address == NULL) panic("List::Memory allocation error!");
	char* tmp = (char*)realloc((void*)(*list), new_size);
	if (tmp == NULL) panic("CharList::Memory allocation error!");
	else {
		list[0] = tmp;
	}
}

void subCharArray(char* from, char* to, int begin, int end)
{
	for (int i = 0; i < (end - begin) + 1; i++) {
		to[i] = from[i + begin];
	}
}
// BUCKET

obj_ptr* initBucket(int size) {
	return (void*)calloc(size, sizeof(void*));
}

void expandBucket(obj_ptr** bucket, int new_size) {
	obj_ptr* tmp = (obj_ptr*)realloc((obj_ptr)(*bucket), sizeof(obj_ptr)*new_size);
	if (tmp == NULL) panic("Bucket tmp :: Memory allocation error!");
	*bucket = tmp;
}

void pushToBucket(obj_ptr** bucket, int* bucket_size, obj_ptr obj) {
	expandBucket(bucket, (*bucket_size) + 1);
	(*bucket)[(*bucket_size)] = obj;
	*bucket_size = *bucket_size + 1;
}

void freeBucket(obj_ptr* bucket, int bucket_size) {
	if (bucket == 0) return;
	for (int i = 0; i < bucket_size; i++) {
		if (bucket[i] == 0) break;
		free(bucket[i]);
	}
	if (bucket != 0) {
		free(bucket);
	}
}

void _freeBucket(obj_ptr* bucket, int bucket_size)
{
	if (bucket == 0) return;
	for (int i = 0; i < bucket_size; i++) {
		if (bucket[i] == 0) break;
		//TODO ERROR
		///free(bucket[i]);
	}
	if (bucket != 0) {
		free(bucket);
	}
}

// INT64

void expand64Array(__int64** array, int new_size){
	__int64* tmp = (__int64*)realloc((void*)(*array), new_size * sizeof(__int64));
	if (tmp == NULL) panic("List::Memory allocation error!");
	else *array = tmp;
}

void fill64Array(__int64* array, int len, __int64 value) {
	for (int i = 0; i < len; i++) {
		array[i] = value;
	}
}

void copy64Array(__int64* from, __int64* to, int begin, int end){
	for (int i = 0; i < (end - begin) + 1; i++) {
		to[i] = from[i + begin];
	}
}

void putTo64Array(__int64** list, int* size, __int64 n){
	expand64Array(list, (*size) + 1);
	(*list)[(*size)] = n;
	*size = *size + 1;
}

// DOUBLE

void expandDoubleArray(double** array, int new_size) {
	double* tmp = (double*)realloc((void*)(*array), new_size * sizeof(double));
	if (tmp == NULL) panic("List::Memory allocation error!");
	else *array = tmp;
}

void putToDoubleArray(double** list, int* size, double n) {
	expandDoubleArray(list, (*size) + 1);
	(*list)[(*size)] = n;
	*size = *size + 1;
}