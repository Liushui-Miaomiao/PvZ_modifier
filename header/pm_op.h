#ifndef _PM_OP_H_
#define _PM_OP_H_

#include "public\headergr.h"

/*pm_op - Process Memory Operation*/
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwSize,int iLevel,...);
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwValue,DWORD dwSize,int iLevel,...);

#endif
