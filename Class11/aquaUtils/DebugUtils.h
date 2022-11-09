#pragma once
#include <stdio.h>
#include <stdlib.h>
#define string const char*

void panic(string msg);
void h1dd3n_p4n1c();
int panic_e(string msg);
void panic_NPE();

void printIntArray(int* array, int len);
void setLastError(int channel, string value);
string getLastError(int channel);
void setTemp(int channel, string value);
string getTemp(int channel);