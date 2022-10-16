#include <stdio.h>
#include "pch.h";
#include <string.h>

#define MAX_STR_LENGTH 1024

int main() {

	printf("> ");
	const char input[512];
	if(!scanf_s(F_Scan512, &input, 512))
		panic("Wrong input! [0]");
	int readed = 0;
	string* N_M = split(trim(input), ' ', &readed);
	if (readed != 2) panic("Wrong input! It should be 2 numbers");
	int N = atoi(N_M[0]);
	int M = atoi(N_M[1]);
	freeBucket(N_M, readed);

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
		printf(str_bucket[i]);
		printf(" (len = %d)", len);
		printf("\n");
	}

	freeBucket(str_bucket, bucket_size);
}