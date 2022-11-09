#include <stdio.h>
#include <stdlib.h>

const char* _data = "Time to sleep!\n\0Great morning to coffee!\n";

int main(int ac, char** av) // <- 7 14 21 28 4 22
{
	int mem = 0, day = 0;
	for (int i = 1;i < ac;i++) mem |= 1 << atoi(av[i]);
	goto entry;
	while (scanf_s("%d", &day)) {
		if (day < 1) return 0;
		printf(_data + !(1 << day & mem)*16);
		entry: printf("\nEnter a day number:\n> ");
	}
	return 0;
}