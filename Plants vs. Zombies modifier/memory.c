#include "public_header.h"

#include "memory.h"

extern HANDLE g_hProcess;

static DWORD GetMemory(DWORD dwBaseAddr, DWORD dwSize, int iLevel, va_list argptr) {
	DWORD dwTempAddr;
	dwTempAddr = dwBaseAddr;

	int i;
	if (iLevel != 0) {																//ƫ�Ʋ�Ϊ0
		for (i = 0; i < iLevel; i++) {												//����ƫ���ۼӵ�ַ
			ReadProcessMemory(g_hProcess, (LPCVOID)dwTempAddr, &dwTempAddr, dwSize, NULL);
			dwTempAddr += va_arg(argptr, DWORD);
		}
	}

	va_end(argptr);

	return dwTempAddr;
}

DWORD ReadMemory(DWORD dwBaseAddr, DWORD dwSize, int iLevel, ...) {
	va_list argptr;																	//�ɱ�����б�ָ��
	va_start(argptr, iLevel);														//ָ����iLevel֮���Ϊ����ָ��

	if (dwSize > 4) {
		dwSize = 4;
	}

	DWORD dwFinalAddr;
	dwFinalAddr = GetMemory(dwBaseAddr, dwSize, iLevel, argptr);

	va_end(argptr);																	//ʹ������ͷ�ָ��

	DWORD dwValue;
	ReadProcessMemory(g_hProcess, (LPCVOID)dwFinalAddr, &dwValue, dwSize, NULL);

	return dwValue;
}

BOOL WriteMemory(DWORD dwBaseAddr, DWORD dwValue, DWORD dwSize, int iLevel, ...) {
	va_list argptr;																	//�ɱ�����б�ָ��
	va_start(argptr, iLevel);														//ָ����iLevel֮���Ϊ����ָ��

	if (dwSize > 4) {
		dwSize = 4;
	}

	DWORD dwFinalAddr;
	dwFinalAddr = GetMemory(dwBaseAddr, dwSize, iLevel, argptr);

	va_end(argptr);																	//ʹ������ͷ�ָ��

	return WriteProcessMemory(g_hProcess, (LPVOID)dwFinalAddr, &dwValue, dwSize, NULL);
}