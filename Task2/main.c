#include <stdio.h>

#include <stdio.h>
#include "aquaLib/pch.h"
#include <string.h>

#define MAX_STR_LENGTH 1024

string reverseString(string, int);

int main(int argc, string* argv) {

	if (argc < 3) panic("Not enought args, should be only 2");
	if (argc > 3) panic("Too many arguments, should be only 2");

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);

	int bucket_size = 0;
	CharList input_buffer;
	string* str_bucket = initBucket(1);

	for (int i = 0; i < N; i++) {
		const char input_buffer[MAX_STR_LENGTH];
		printf("> ");
		if (!scanf_s("%s", &input_buffer, M)) {
			panic("Wrong input! [1]");
		}
		pushToBucket(
			&str_bucket,
			&bucket_size,
			str_copy(input_buffer)
		);
	}

	printf("\n%d string were entered:\n", bucket_size);
	for (int i = 0; i < N; i++) {
		int len = strlen(str_bucket[i]);
		string s = reverseString(str_bucket[i], len);
		printf(s); free(s);
		printf(" (len = %d)", len);
		printf("\n");
	}

	freeBucket(str_bucket, bucket_size);
}

string reverseString(string nt_str, int len){
	char* result = (char*)initList(0, sizeof(char));
	int j = 0;
	for (int i = 0; i < len; i++) {
		pushToCharList(&result, &j, nt_str[len - 1 - i]);
	}
	return buildString(result, j);
}