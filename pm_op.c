/*Process Memory Operation*/

#include "header\pm_op.h"

#include <stdarg.h>

static DWORD getMemory(HANDLE hProcess,DWORD dwBaseAddr,DWORD dwSize,int iLevel,va_list argptr);

/*�õ������ڴ��ַ*/
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
		printf("ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",dwTempAddr,iValue);
	#endif
	
	return dwTempAddr;
}

/*��ȡ������ָ���ڴ�����*/
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

/*������д��ָ���ڴ�*/
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
