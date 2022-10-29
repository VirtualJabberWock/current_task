#include "..\aquaUtils\pch.h"

void readLinesFromFile(string filename, StringV* out);
void writeLinesToFile(string filename, StringV* lines);
string intToString(int value);

int main(int argc, string* argv) {

	if (argc != 2) panic("Usage: ...\\Task2.exe <filename>");
	StringV sv;
	InitStringV(&sv);
	sv.put(&sv, "");
	readLinesFromFile(argv[1], &sv);
	sv.ptr[0] = intToString(sv.size - 1);
	writeLinesToFile(argv[1], &sv);
}


void readLinesFromFile(string filename, StringV* sv_ptr) {
	FILE* f;
	openFile_s(&f, filename);
	readAllLines_s(f, sv_ptr);
	closeFile(f);
}

void writeLinesToFile(string filename, StringV* data) {
	FILE* f;
	openFileW_s(&f, filename);
	writeAllLines_s(f, data);
	closeFile(f);
}

string intToString(int value) {
	char* buf = initArray(16, sizeof(char));
	if (_itoa_s(value, buf, 16, 10) != 0) {
		panic("Overflow");
	}
	return buildString(buf, 16);
}