#pragma once

#include <windows.h>
#include "..\aquaUtils\StringUtils.h"
#define APP_NAME L"Terminal.exe"

#if _WIN32 || _WIN64
#if _WIN64
#define address_t __int64
#else
#define address_t __int32
#endif
#endif

void (*exitPtr) (int);

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		exitPtr(0);
		return TRUE;
	}

	return FALSE;
}

void hookExitProccess(void* f) {
	exitPtr = f;
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
}

static int UnlockMemory(address_t adr) {
	DWORD OldProtection;
	if (VirtualProtect((void*)adr, 128, PAGE_EXECUTE_READWRITE, &OldProtection))
	{
		return 1;
	}
	else {
		return 0;
	}
}

static int replaceInt64(address_t adr, address_t value) {
	address_t out_value = value;
	if (adr == 0) {
		MessageBoxW(0, L"null", L"null", MB_ICONINFORMATION);
		return 0;
	}
	memcpy((void*)adr, (const void*)(&out_value), sizeof(address_t));
	return 1;
}

static int hookFunction(LPCWSTR module_name, address_t shift, string func) {
	address_t address = (address_t) GetModuleHandleW(module_name);
	HMODULE context = GetModuleHandleW(APP_NAME);
	if (context == 0) {
		panic("HOOKER: Bad module or APP_NAME");
		return 0;
	}
	if (address == 0) panic("HOOKER: Can't find module");
	address = address + shift;
	address_t value = (address_t) GetProcAddress(context, func);
	if (value == 0) return 0;
	int a = UnlockMemory(address);
	if (a == 1) a = replaceInt64(address, value);
	return a;
}