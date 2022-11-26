#include "DebugUtils.h"
#include <Windows.h>
#include "ArrayUtils.h"

static string_t last_error_channel0;
static string_t last_error_channel1;
static string_t last_error_channel2;
static string_t last_error_channel3;

static string_t debug_channel0;
static string_t debug_channel1;
static string_t debug_channel2;


int panic(string_t msg) {
	printf_s(msg);
	printf_s("\n");
	system("pause");
	ExitProcess(1);
	return 0;
}

int panic_e(string_t class, string_t local, string_t msg)
{
	printf(class);
	printf(".%s :: ", local);
	panic(msg);
	return 0;
}

void h1dd3n_p4n1c()
{
	Sleep(10000); // TODO: replace it with OS(Windows) checkers for process response
	panic("[hidden panic!] Unexpected catastrophic waiting..."
		"\n and thread SUS(pend)!\nTerminate process...");
}

int panic_NPE(void* func, string_t obj)
{
	string_t func_name = initArray(64, sizeof(char));
	sprintf_s(func_name, 64, "%p", func);
	printf("NullPointerException: at %s, objectName: [%s]", func_name, obj);
	free(func_name);
	panic("");
	return 0;
}

void printIntArray(int* array, int len) {
	printf("\n");
	for (int i = 0; i < len; i++) {
		printf_s("%d ", array[i]);
	}
	printf("\n");
}

void setLastError(int channel, string_t value) {
	if (channel == 0) last_error_channel0 = value;
	if (channel == 1) last_error_channel1 = value;
	if (channel == 2) last_error_channel2 = value;
	if (channel == 3) last_error_channel3 = value;
}

string_t getLastError(int channel) {
	if (channel == 0) return last_error_channel0;
	if (channel == 1) return last_error_channel1;
	if (channel == 2) return last_error_channel2;
	if (channel == 3) return last_error_channel3;
	return "Unknown channel";
}

void setTemp(int channel, string_t value) {
	if (channel == 0) debug_channel0 = value;
	if (channel == 1) debug_channel1 = value;
	if (channel == 2) debug_channel2 = value;
}

string_t getTemp(int channel) {
	if (channel == 0) return debug_channel0;
	if (channel == 1) return debug_channel1;
	if (channel == 2) return debug_channel2;
	return "Unknown channel";
}

int isPositive(int n)
{
	return (n < 0);
}
