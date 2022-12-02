#include <stdio.h>
#include "../../aquaUtils/StringUtils.h"

int countNotUniqueSymbols(string_t str);


int main(int argc, string_t* argv) {

	if (argc != 2) return printf("Invalid args!");

	int c = countNotUniqueSymbols(argv[1]);
	printf("%d", c);
}

// <bool>[512](64bytes) ~ int[16](64 bytes) < char[256] (256 bytes)
int countNotUniqueSymbols(string_t str) {
	int r = 0;
	int i = 0;
	int bitset[16] = { 0 };
	while (str[i] != '\0') {
		if ((bitset[str[i] / 32] & 1 << (str[i] % 32)) != 0) {
			r += !(bitset[str[i] / 32 + 8] & (1 << (str[i] % 32)));
			bitset[str[i] / 32 + 8] |= (1 << str[i] % 32);
		}
		bitset[str[i] / 32] |= (1 << (str[i] % 32));
		i++;
	}
	return r;
}