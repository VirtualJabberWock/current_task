#include "../../aquaUtils/pch.h";
#include "../../aquaUtils/FileUtils.h"
#include "../../aquaUtils/BasicDataStructs.h"

typedef struct tagFileData{
	StringV* sv;
	IntV* lengths;
	List* lens_list;
	int N;
	int count;
} FileData;

int findMinimumFairLimit(List* l, int N);
FileData* scanFromFile(string_t filename);

int main() {
	FileData* fdata = scanFromFile("input.txt");
	printf("WORDS: %d, N = %d\n", fdata->lengths->size, fdata->N);
	unsigned int len_filter = 0xffffffff;
	if (fdata->N != fdata->count) {
		len_filter = findMinimumFairLimit(fdata->lens_list, fdata->N);
	}
	printf("\n\nFILTER = %u\n\n", len_filter);
	int c = 0;
	for (int i = 0; i < fdata->sv->size; i++) {
		if (fdata->lengths->ptr[i] < len_filter) continue;
		if (c >= fdata->N) break;
		printf("%s ", fdata->sv->ptr[i]);
		c++;
	}
	printf("\n\n");
}

FileData* scanFromFile(string_t filename)
{
	FileData* data = malloc(sizeof(FileData));
	if (data == 0) return panic("Unexpected error");
	data->sv = malloc(sizeof(StringV));
	data->lengths = malloc(sizeof(IntV));
	data->lens_list = NewList();
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
		int len = SUS_getStringLength(data->sv->ptr[i]);
		data->lengths->put(data->lengths, len);
		data->lens_list->push(data->lens_list, len);
	}
	return data;
}

int findMinimumFairLimit(List* lens, int N)
{
	int _n = N;
	LongV nodeToRemove; InitLongV(&nodeToRemove);
	nodeToRemove.put(&nodeToRemove, -1);
	while (_n > 0) {
		int _max = 0;
		node* current = lens->head; 
		printf("\nSEARCH :: ");
		while (current != NULL) {
			if (current->value > _max) {
				_max = current->value;
				nodeToRemove.ptr[0] = (__int64) current;
				nodeToRemove.size = 1;
				printf("m = %d, ", _max);
			}else if(current->value == _max) {
				nodeToRemove.put(&nodeToRemove, (__int64)current);
			}
			current = current->next;
		}
		_n -= nodeToRemove.size;
		if (_n <= 0) return _max;
		printf("FOUND = %d, _n = %d; [%d]\n", _max, _n, nodeToRemove.size);
		for (int i = 0; i < nodeToRemove.size; i++) {
			ListNodeRemove(lens, (node*)nodeToRemove.ptr[i]);
		}
		nodeToRemove.size = 1;
	}
	return 0;
}
