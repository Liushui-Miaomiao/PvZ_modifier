#ifndef _P_OP_H_
#define _P_OP_H_

#include "public\headergr.h"

/*p_op - Process Operation*/
BOOL getProcessPidByName(const char cProcessName[],DWORD &dwPid);
void close(void);

#endif
