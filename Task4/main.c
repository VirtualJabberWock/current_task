
#include "pch.h"

string* getDecryptedStrings(string fn, string** out_v, int* out_c);
int compareStrings(string str1, string str2);

int main(int argc, string* argv) {

	if (argc < 2) panic("Bas syntax. Usage: Task4.exe <filename>");
	if (argc > 2) panic("Too many arguments, should be only 1");

	string filename = argv[1];

	int lines_c = 0;
	string* decrypted;
	getDecryptedStrings(filename, &decrypted, &lines_c);

	for (int i = 0; i < lines_c; i++) {
		for (int j = 1; j < lines_c; j++) {
			if(compareStrings(decrypted[j-1], decrypted[j])) {
				string tmp = decrypted[j-1];
				decrypted[j - 1] = decrypted[j];
				decrypted[j] = tmp;
			}
		}
	}

	for (int i = 0; i < lines_c; i++) {
		printf(decrypted[i]);
		printf("\n");
	}
	_freeBucket(decrypted, lines_c);
}

string* getDecryptedStrings(string filename, string** out_v, int* out_len) {
	
	FILE* f_handle;
	openFileText_s(&f_handle,filename);
	string* sb = initBucket(0);
	int readed = 0, out_s = 0;
	readAllLines_s(f_handle, &sb, &readed);
	closeFile(f_handle);

	for (int i = 0; i < readed; i++) {
		int parts = 0;
		string* words = split(trim(sb[i]), ' ', &parts);
		for (int j = 0; j < parts; j++) {
			int len;
			CharList cl = initList(0, sizeof(char));
			str_unlock(words[j], &len, &cl);
			for (int z = 0; z < len; z++) {
				cl[z] = words[j][(z+len/2)%len];
			} 
			words[j] = buildString(cl, len);
		}
		sb[i] = str_bucket_assemble(words, parts, ' ');
		free(words);
	}
	*out_len = readed;
	*out_v = sb;
}


/*
COMPARE :: (str1='a',str2='b' : return 0) (str1='b',str2='a' : return 1)
*/
int compareStrings(string str1, string str2) {
	int min_len = min(strlen(str1), strlen(str2));
	for (int i = 0; i < min_len; i++) {
		if (str1[i] == str2[i]) continue;
		if (str1[i] > str2[i]) return 1; // swap
		else return 0; // no swap
	}
	return 0;
}