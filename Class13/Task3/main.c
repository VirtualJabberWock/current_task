#include <stdio.h>
#include "../../aquaUtils/pch.h"
#include <limits.h>

int uint_max[10] = { 4,2,9,4,9,6,7,2,9,5 };

int injectData(int argc, int* T, int* Q) {
	if (argc == 3) return 0;
	*T = 12; // [1, 84]
	*Q = 40; // [1, 1'000'000'000]
	return 1;
}

void gotoxy(int x, int y);
int current_line = 0;

int displayA(int T);
int displayB(int Q);
int displayC(int T);
int displayD(int Q);

int main(int argc, string_t* argv) {

	int T = 0; int Q = 0;
	if (!injectData(argc, &T, &Q)) {
		T = atoi(argv[1]);
		Q = atoi(argv[2]);
	}
	if ((T < 1) || (Q < 1)) panic("Invalid data!");
	displayA(T);
	displayB(Q);
	displayC(T);
	displayD(Q);
	return 0;
}

int displayA(int T)
{
	printf("A: ");
	printf("%d"+(T % 9 == 0)*2, T % 9);
	for (int i = 0; i < T / 9; i++) printf("9");
	current_line++;
	return printf("\n");
}

int displayB(int q)
{
	printf("B: ");
	if (q == 1) return printf("1");
	for (int i = 9; i > 1; i--) {
		while (q % i == 0) {
			printf("%d", i);
			q /= i;
		}
	}
	if (q != 1) {
		gotoxy(3, current_line);
		printf("doesn't exists");
	}
	current_line++;
	return printf("\n");
}

int displayC(int T) // [1, 84] --> sumOfDigits(3'999'999'999) = 84; 
{
	int result[10] = { 4,0,0,0,0,0,0,0,0,0 };
	int max_sum[10] = { 77,77,72,72,69,67,60,60,57,57 }; //for UINT_MAX
	int left_over = T;
	int overflowFlag = 1;
	for (int i = 0; i < 10; i++) {
		if ((T > max_sum[i]) && overflowFlag) {
			uint_max[i] = uint_max[i] - 1;
			for (int j = i + 1; j < 10; j++) uint_max[j] = 9;
			overflowFlag = 0;
		}
		if (left_over == 0) break;
		if (left_over > uint_max[i])
			left_over -= result[i] = uint_max[i];
		else {
			result[i] = left_over; break;
		}
	}
	printf("C: ");
	for(int j = 0; j<10; j++) printf("%d", result[j]);
	current_line++;
	return printf("\n");
}          

int displayD(int Q) {
	printf("D: ");
	if (Q < 4) return printf("%d111111111", Q);
	int isNumberLessThan2Billion = 1;
	IntV iv; IntVP result = &iv; InitIntV(result);
	for (int i = 4; i > 0; i--) {
		if (Q % i == 0) {
			Q /= i; result->put(result, i); break;
		}
	} // 4 steps max
	int near_ = (result->ptr[0] == 4);
	for (int i = 9; i > 1; i--) {
		for (int j = (near_ ? uint_max[10 - i] : i); j > (near_ ? 1 : i - 1); j--) {
			while (Q % j == 0) {
				result->put(&iv, j);
				Q /= j;
			}
		}
	} // near_ in [75 of 100] cases equals 0 => we have only 10 steps of factorzitaion
	// TOTAL: steps 10 * (1[75%] ? 9[7.5%]) * (factor_steps) ====> ~ 20 steps + factorization
	if ((Q != 1) || (result->size >= 10)) 
		return printf("doesn't exists\n");
	int c = result->size;
	for (int i = 0; i < 10-c; i++) result->put(result, 1);
	for (int i = 0; i < result->size; i++) 
		printf("%d", result->ptr[i]);
	current_line++;
	return printf("\n");
}

void gotoxy(int x, int y){
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
