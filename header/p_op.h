#ifndef _P_OP_H_
#define _P_OP_H_

#include "public\headergr.h"

#include <tlhelp32.h>
#include <stdlib.h>

/*p_op - Process Operation*/
BOOL getProcessPidByName(const char cProcessName[],DWORD &dwPid);
void setColor(WORD wColor);
void close(void);

#endif
