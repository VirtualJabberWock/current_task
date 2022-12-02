#include <stdio.h>
#include "../../aquaUtils/pch.h"

string_t lessValueIfExists(string_t);
void swap(char* a, char* b);
void bubbleSort(char* arr, int n);

int main() {
	int N = 0;
    printf("> ");
	int s = scanf_s("%d", &N);
	if (s == 0) panic("Inavlid Input!");
    string_t x = lessValueIfExists(SUS_format1024("%d", N));
    printf("%s", x);
}

void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

string_t lessValueIfExists(string_t digits)
{
    int i, j;
    int n = SUS_getStringLength(digits);
    for (i = n - 1; i > 0; i--)
        if (digits[i] < digits[i - 1])
            break;
    if (i == 0) return "0"; // don't exists, because every digit in order "1234..."
    int x = digits[i - 1], index_to_swap = i;
    for (j = i; j < n; j++)
        if (digits[j] < x && digits[j] > digits[index_to_swap])
            index_to_swap = j;
    swap(&digits[index_to_swap], &digits[i - 1]);
    bubbleSort(digits + i, n - i); //sort from number[i] to number[n-1]
    return digits;
}

void bubbleSort(char* arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] < arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}