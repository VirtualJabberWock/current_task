#include <stdio.h>
#include "../../aquaUtils/pch.h"

#define ELEVENS 1111111111111111 

int injectData(int argc, int* T, int* Q) {
	if (argc == 3) return 0;
	*T = 12; // [1, 84]
	*Q = 107; // [1, 1'000'000'000]
	return 1;
}

int displayA(int T, int Q);
int displayB(int T, int Q);
int displayC(int T, int Q);

int main(int argc, string_t* argv) {

	megaPONPONPONPONPONPON("Joker");
	/*int T = 0; int Q = 0;
	if (!injectData(argc, &T, &Q)) {
		T = atoi(argv[1]);
		Q = atoi(argv[2]);
	}
	displayA(T, Q);
	displayB(T, Q);*/
}

int displayA(int T, int Q)
{
	printf("A: ");
	printf("%d"+(T % 9 == 0)*2, T % 9);
	for (int i = 0; i < T / 9; i++) printf("9");
	return printf("\n");
}

int displayB(int T, int Q)
{
	printf("B: ");
	int z = 0;
	int t = 1;
	int q = Q; // copy
	//corner case:
	if (q < 10) return printf("%d\n", q);
	for (int i = 9; i > 1; i--) {
		while (q % i == 0) {
			z += i * t;
			t *= 10;
			q /= i;
		}
	}
	if (q == 1)
		printf("%d", z);
	else
		printf("doesn't exists");
	printf("\n");
}

int displayC(int T, int Q)
{
	printf("A: ");
	printf("%d" + (T % 9 == 0) * 2, T % 9);
	for (int i = 0; i < T / 9; i++) printf("9");
	return printf("\n");
}
