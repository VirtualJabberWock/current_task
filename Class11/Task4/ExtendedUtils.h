#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <corecrt_wstring.h>

int WideToASCII(const wchar_t* in, char* out) {
	char buf[128];
	size_t len;
	errno_t status = wcstombs_s(&len, buf, 128, in, wcslen(in));
	if (status != 0) return 0;
	if (len < 1) return 0;
	for (int i = 0; i < len; i++) {
		out[i] = buf[i];
	}
	out[len] = '\0';
	return 1;
}