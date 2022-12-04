#include "../../aquaUtils/pch.h";

void IntegerBubbleSort(int* arr, int n);
void swap(int* a, int* b);

int main(int argc, string_t* argv) {
	if (argc <= 2) return printf("Invalid args!");
	IntV lengths; InitIntV(&lengths);
	IntV lengths_origin; InitIntV(&lengths_origin);
	int N = atoi(argv[1]);
	if (N > argc) printf("Invalid args!");
	for (int i = 2; i < argc; i++) {
		int len = SUS_getStringLength(argv[i]);
		lengths_origin.put(&lengths_origin, len);
		lengths.put(&lengths, len);
	}
	IntegerBubbleSort(lengths.ptr, lengths.size);
	unsigned int filter_len = 0xffffffff;
	if (N != lengths.size) filter_len = lengths.ptr[N];
	int c = 0;
	for (int i = 0; i < argc; i++) {
		if (lengths_origin.ptr[i] < filter_len) continue;
		if (c >= N) break;
		printf("%s ", argv[i+2]);
		c++;
	} 
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void IntegerBubbleSort(int* arr, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] < arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}
