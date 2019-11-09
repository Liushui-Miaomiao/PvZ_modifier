/*Process Memory Operation*/

#include "header\pm_op.h"

#include <stdarg.h>

static DWORD getMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwSize,int iLevel,va_list argptr);

/*得到最终内存地址*/
static DWORD getMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwSize,int iLevel,va_list argptr){
	DWORD dwTempAddr;
	dwTempAddr=dwBaseAddr;
	
	int i;
	if(iLevel!=0){
		for(i=0;i<iLevel;i++){
			ReadProcessMemory(hProcess,(LPCVOID)dwTempAddr,&dwTempAddr,dwSize,NULL);
			dwTempAddr+=va_arg(argptr,DWORD);
		}
	}
	
	va_end(argptr);
	
	#if DEBUG
		int iValue;
		ReadProcessMemory(hProcess,(LPCVOID)dwTempAddr,&iValue,dwSize,NULL);
		printf("偏移地址为：%x，读取的值为：%d\n",dwTempAddr,iValue);
	#endif
	
	return dwTempAddr;
}

/*读取并返回指定内存数据*/
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwSize,int iLevel,...){
	va_list argptr;
	va_start(argptr,iLevel);
	
	if(dwSize>4){
		dwSize=4;
	}
	
	DWORD dwFinalAddr;
	dwFinalAddr=getMemory(hProcess,dwBaseAddr,dwSize,iLevel,argptr);
	
	va_end(argptr);
	
	DWORD dwValue;
	ReadProcessMemory(hProcess,(LPCVOID)dwFinalAddr,&dwValue,dwSize,NULL);
	
	return dwValue;
}

/*将数据写入指定内存*/
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwValue,DWORD dwSize,int iLevel,...){
	va_list argptr;
	va_start(argptr,iLevel);
	
	if(dwSize>4){
		dwSize=4;
	}
	
	DWORD dwFinalAddr;
	dwFinalAddr=getMemory(hProcess,dwBaseAddr,dwSize,iLevel,argptr);
	
	va_end(argptr);
	
	return WriteProcessMemory(hProcess,(LPVOID)dwFinalAddr,&dwValue,dwSize,NULL);
}
