#include "public_header.h"

#include "modifiy.h"
#include "memory.h"

extern DWORD* p_dwBuffer;

DWORD Limit(DWORD dwValue, DWORD dwMin, DWORD dwMax) {
	if (dwValue < dwMin) {
		dwValue = dwMin;
	}
	if (dwValue > dwMax) {
		dwValue = dwMax;
	}

	return dwValue;
}

BOOL ChangeSunLight() {
	DWORD dwSunLight;
	dwSunLight = Limit(*p_dwBuffer, 0, 9990);

	return WriteMemory(0x006A9EC0, dwSunLight, 4, 2, 0x768, 0x5560);
}