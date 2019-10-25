#ifndef _PM_OP_H_
#define _PM_OP_H_

#include "public\headergr.h"

#include <stdarg.h>

/*pm_op - Process Memory Operation*/
static DWORD getMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwSize,va_list argptr);
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwSize,...);
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwValue,DWORD dwSize,...);

#endif
