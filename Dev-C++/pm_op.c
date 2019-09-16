/*Process Memory Operation*/

#include <stdarg.h>
#include "headgr.h"

/*句柄，基址，偏移级数，数值类型，偏移地址参数列*/
static DWORD getMemory(HANDLE hProcess,DWORD BaseAddr,int level,SIZE_T Size,va_list argptr){
	DWORD tempAddr;
	tempAddr=BaseAddr;
	
	int i;
	if(level!=0){
		for(i=0;i<level;i++){
			ReadProcessMemory(hProcess,(LPVOID)tempAddr,&tempAddr,(SIZE_T)Size,NULL);
			tempAddr+=va_arg(argptr,DWORD);
		}
	}
	
	va_end(argptr);
	
	#if DEBUG
		int value;
		ReadProcessMemory(hProcess,(LPVOID)tempAddr,&value,(SIZE_T)Size,NULL);
		printf("偏移地址为：%x，读取的值为：%d\n",tempAddr,value);
	#endif
	
	return tempAddr;
}

/*句柄，基址，偏移级数，数值类型，偏移地址参数列*/
DWORD readMemory(HANDLE hProcess,DWORD BaseAddr,int level,SIZE_T Size,...){
	va_list argptr;
	va_start(argptr,Size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,BaseAddr,level,Size,argptr);
	
	int value;
	ReadProcessMemory(hProcess,(LPVOID)finalAddr,&value,(SIZE_T)Size,NULL);
	
	va_end(argptr);
	
	return value;
}

/*句柄，基址，偏移级数，写入值，数值类型，偏移地址参数列*/
BOOL writeMemory(HANDLE hProcess,DWORD BaseAddr,int level,DWORD value,SIZE_T Size,...){
	va_list argptr;
	va_start(argptr,Size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,BaseAddr,level,Size,argptr);
	
	va_end(argptr);
	
	return WriteProcessMemory(hProcess,(LPVOID)finalAddr,&value,(SIZE_T)Size,NULL);
}
