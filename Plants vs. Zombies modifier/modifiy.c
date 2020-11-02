#include "public_header.h"

#include "modifiy.h"
#include "memory.h"

extern DWORD* p_dwBuffer;

DWORD Limit(DWORD dwValue, DWORD dwMin, DWORD dwMax);

DWORD Limit(DWORD dwValue, DWORD dwMin, DWORD dwMax) {
	if (dwValue < dwMin) {
		dwValue = dwMin;
	}
	if (dwValue > dwMax) {
		dwValue = dwMax;
	}

	return dwValue;
}

BOOL ChangeSunLight(void) {
	DWORD dwSunLight;
	dwSunLight = Limit(*p_dwBuffer, 0, 9990);

	return WriteMemory(0x006A9EC0, dwSunLight, 4, 2, 0x768, 0x5560);
}

BOOL ChangeMoney(void) {
	DWORD dwMoney;
	dwMoney = Limit(*p_dwBuffer, 0, 99999);

	return WriteMemory(0x006A9EC0, dwMoney, 4, 2, 0x82C, 0x28);
}

BOOL CardNoCD(void) {
	return WriteMemory(0x00487296, 0x1477, 2, 0);
}

BOOL AllowBackStageRun(BOOL b) {
	if (b) {
		return WriteMemory(0x0054EBEF, 0xC3, 1, 0);
	}

	return WriteMemory(0x0054EBEF, 0x57, 1, 0);
}

BOOL ChangeCardNum(void) {
	DWORD dwCardNum;
	dwCardNum = Limit(*p_dwBuffer, 1, 10);

	return WriteMemory(0x006A9EC0, dwCardNum, 4, 3, 0x768, 0x144, 0x24);
}

BOOL AutoCollect(void) {
	return WriteMemory(0x0043158F, 0xEB, 1, 0);
}

BOOL AdventureJumpLevel(void) {
	DWORD dwLevel;
	dwLevel = Limit(*p_dwBuffer, 11, 99) - 10;

	return WriteMemory(0x006A9EC0, dwLevel, 4, 2, 0x82C, 0x24);
}