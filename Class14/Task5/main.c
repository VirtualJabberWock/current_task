#include "../../aquaUtils/pch.h";
#include "../../aquaUtils/FileUtils.h"

void IntegerBubbleSort(int* arr, int n);
void swap(int* a, int* b);

typedef struct tagFileData{
	StringV* sv;
	IntV* lengths;
	int N;
	int count;
} FileData;

FileData* scanFromFile(string_t filename);

int main() {
	FileData* fdata = scanFromFile("input.txt");
	IntV lengths_origin; InitIntV(&lengths_origin);
	lengths_origin.ptr = initArray(fdata->lengths->size, sizeof(int));
	copyIntArray(fdata->lengths->ptr, lengths_origin.ptr, 0, fdata->lengths->size);
	//IntegerBubbleSort(lengths.ptr, lengths.size);
	unsigned int filter_len = 0xffffffff;
	//if (N != fdata->lengths) filter_len = 
	int c = 0;
	for (int i = 0; i < fdata->sv->size; i++) {
		if (lengths_origin.ptr[i] < filter_len) continue;
		if (c >= fdata->N) break;
		printf("%s ", fdata->sv->ptr[i]);
		c++;
	}
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


FileData* scanFromFile(string_t filename)
{
	FileData* data = malloc(sizeof(FileData));
	if (data == 0) return panic("Unexpected error");
	data->sv = malloc(sizeof(StringV));
	data->lengths = malloc(sizeof(IntV));
	if ((data->sv == 0) || (data->lengths == 0))
		return panic("Unexpected error");
	InitStringV(data->sv); InitIntV(data->lengths);
	FILE* f;
	openFile_s(&f, filename);
	StringV lines; InitStringV(&lines);
	readAllLines_s(f, &lines);
	if (lines.size != 2) panic("Invalid data!");
	data->N = atoi(lines.ptr[0]);
	data->sv->ptr = SUS_split(lines.ptr[1], ' ', &data->sv->size);
	if (data->N > data->sv->size) panic("Invalid request!");
	closeFile(f);
	for (int i = 0; i < data->sv->size; i++) {
		data->lengths->put(data->lengths, SUS_getStringLength(data->sv->ptr[i]));
	}
	return data;
}

void IntegerBubbleSort(int* arr, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] < arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}
