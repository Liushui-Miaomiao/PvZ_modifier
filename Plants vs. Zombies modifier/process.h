#pragma once

void Init(void);
BOOL OpenGameProcess(void);
BOOL GetProcessPidByName(char* cProcessName, DWORD *dwPid);
void Pause(void);
void Close(void);