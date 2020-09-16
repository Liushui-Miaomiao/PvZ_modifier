#include "public_header.h"

#include "memory.h"

extern HANDLE g_hProcess;

static DWORD GetMemory(DWORD dwBaseAddr, DWORD dwSize, int iLevel, va_list argptr) {
	DWORD dwTempAddr;
	dwTempAddr = dwBaseAddr;

	int i;
	if (iLevel != 0) {																//偏移不为0
		for (i = 0; i < iLevel; i++) {												//根据偏移累加地址
			ReadProcessMemory(g_hProcess, (LPCVOID)dwTempAddr, &dwTempAddr, dwSize, NULL);
			dwTempAddr += va_arg(argptr, DWORD);
		}
	}

	va_end(argptr);

	return dwTempAddr;
}

DWORD ReadMemory(DWORD dwBaseAddr, DWORD dwSize, int iLevel, ...) {
	va_list argptr;																	//可变参数列表指针
	va_start(argptr, iLevel);														//指定从iLevel之后的为引用指针

	if (dwSize > 4) {
		dwSize = 4;
	}

	DWORD dwFinalAddr;
	dwFinalAddr = GetMemory(dwBaseAddr, dwSize, iLevel, argptr);

	va_end(argptr);																	//使用完毕释放指针

	DWORD dwValue;
	ReadProcessMemory(g_hProcess, (LPCVOID)dwFinalAddr, &dwValue, dwSize, NULL);

	return dwValue;
}

BOOL WriteMemory(DWORD dwBaseAddr, DWORD dwValue, DWORD dwSize, int iLevel, ...) {
	va_list argptr;																	//可变参数列表指针
	va_start(argptr, iLevel);														//指定从iLevel之后的为引用指针

	if (dwSize > 4) {
		dwSize = 4;
	}

	DWORD dwFinalAddr;
	dwFinalAddr = GetMemory(dwBaseAddr, dwSize, iLevel, argptr);

	va_end(argptr);																	//使用完毕释放指针

	return WriteProcessMemory(g_hProcess, (LPVOID)dwFinalAddr, &dwValue, dwSize, NULL);
}