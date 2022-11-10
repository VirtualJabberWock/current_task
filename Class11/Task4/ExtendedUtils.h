#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <corecrt_wstring.h>
#include <Windows.h> 

int WideToASCII(const wchar_t* in, char* out) {
	char buf[256];
	size_t len;
	errno_t status = wcstombs_s(&len, buf, 256, in, wcslen(in));
	if (status != 0) return 0;
	if (len < 1) return 0;
	for (int i = 0; i < len; i++) {
		out[i] = buf[i];
	}
	out[len] = '\0';
	return 1;
}

string WinRequestForOpenFile()
{
	OPENFILENAME ofn = { 0 };
	TCHAR szFile[260] = { 0 };
	// Initialize remaining fields of OPENFILENAME structure
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = 0;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.wallet\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		char* buf = initArray(256, sizeof(char));
		WideToASCII(ofn.lpstrFile, buf);
		return buf;
	}
	return "";
}