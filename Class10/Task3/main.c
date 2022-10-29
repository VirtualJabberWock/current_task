#include "..\aquaUtils\pch.h"

void readLinesFromFile(string filename, StringV* out);
void writeLinesToFile(string filename, StringV* lines);
void transformStringV(StringV* sv, string transformer(string));
string invertCase(string str);
string clearSpaces(string str);


int main(int argc, string* argv) {
	if (argc != 2) panic("Usage: ...\\Task2.exe <filename>");
	StringVP lines = NewStringV();
	readLinesFromFile(argv[1], lines);
	transformStringV(lines, invertCase);
	transformStringV(lines, clearSpaces);
	writeLinesToFile(argv[1], lines);
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

void transformStringV(StringV* sv, string transformer(string))
{
	for (int i = 0; i < sv->size; i++) {
		sv->ptr[i] = transformer(sv->ptr[i]);
	}
}

string invertCase(string str) {
	int len = SUS_getStringLength(str);
	char* a = initArray(len, sizeof(char));
	for (int i = 0; i < len; i++) {
		char c = str[i];
		a[i] = (c^' ')*(((c>'@')&(c<'['))|((c>'`')&(c<'{')));
	}
	return buildString(a, len);
}

/*
'0100 0000' @
 ...A-Z...
'0101 1011' [
	...
'0110 0000' `
 ...a-z...
'0111 1011' {
*/

string clearSpaces(string str)
{
	str = SUS_str_f(str, " ", '\t');
	str = SUS_clearDublicateSpaces(str);
	return str;
}






