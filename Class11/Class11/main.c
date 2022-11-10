#include "..\aquaUtils\StringUtils.h"
#include "..\aquaUtils\ArrayUtils.h"

int checkForAnagram(string word, string base, int x_s);

#define strlen(x) SUS_getStringLength(x) //export

int main(int argc, string* argv) {

	if (argc != 2) panic("Usage: ..\\Task2.exe <string>");
	string buf[512] = { 0 };
	printf("Base word: "); printf(argv[1]);
	int base_len = strlen(argv[1]);
	int s = 0;

	while(1) {
		printf("\nEnter a string:\n> ");
		s = checkForAnagram(gets_s(buf, 512),argv[1], base_len);
		if ((char)buf[0] == 0) break;
		if (s) printf("True!");
		else printf("False!");
	}
}

int checkForAnagram(string word, string base, int b_len)
{
	int w_len = strlen(word);
	if (w_len > b_len) return 0; //corner case
	char* arr = initArray(64, sizeof(char));
	for (int i = 0; i < w_len; i++) arr[(char)word[i]-'A']++;
	for (int i = 0; i < b_len; i++) arr[(char)base[i]-'A']--;
	for (int i = 0; i < 64; i++) if(arr[i] > 0) return 0;
	return 1;
}
