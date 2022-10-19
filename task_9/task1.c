#include "pch.h"

int main() {
	int n = 0;
	printf("> ");
	if (!scanf_s("%d", &n)) panic("Bad input!");
	printf("%d", fib(n));

}

int fib(int N) {
	if (N < 0)
		panic("Sequence number cannot be negative!");
	if (N == 0)
		return 0;
	if (N == 1)
		return 1;
	if (N > 128) h1dd3n_p4n1c();
	return (fib(N - 1) + fib(N - 2));
}