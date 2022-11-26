#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define string_t const char*


static char isDgbHelpLoaded = 0;

int panic(string_t msg);
int panic_e(string_t class, string_t local, string_t msg);
void h1dd3n_p4n1c();
int panic_NPE(void* func, string_t obj);

void printIntArray(int* array, int len);
void setLastError(int channel, string_t value);
string_t getLastError(int channel);
void setTemp(int channel, string_t value);
string_t getTemp(int channel);
int isPositive(int n);

