#pragma once

DWORD ReadMemory(DWORD dwBaseAddr, DWORD dwSize, int iLevel, ...);
BOOL WriteMemory(DWORD dwBaseAddr, DWORD dwValue, DWORD dwSize, int iLevel, ...);