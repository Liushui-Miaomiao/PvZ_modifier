/*Process Memory Operation*/

#include <stdarg.h>
#include "headgr.h"

/*�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������*/
static DWORD getMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,SIZE_T size,va_list argptr){
	DWORD dwTempAddr;
	dwTempAddr=dwBaseAddr;
	
	int i;
	if(iLevel!=0){
		for(i=0;i<iLevel;i++){
			ReadProcessMemory(hProcess,(LPVOID)dwTempAddr,(LPVOID)&dwTempAddr,(SIZE_T)size,NULL);
			dwTempAddr+=va_arg(argptr,DWORD);
		}
	}
	
	va_end(argptr);
	
	#if DEBUG
		int iValue;
		ReadProcessMemory(hProcess,(LPVOID)dwTempAddr,(LPVOID)&iValue,(SIZE_T)size,NULL);
		printf("ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",dwTempAddr,iValue);
	#endif
	
	return dwTempAddr;
}

/*�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������*/
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,SIZE_T size,...){
	va_list argptr;
	va_start(argptr,size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,dwBaseAddr,iLevel,size,argptr);
	
	va_end(argptr);
	
	int iValue;
	ReadProcessMemory(hProcess,(LPVOID)finalAddr,(LPVOID)&iValue,(SIZE_T)size,NULL);
	
	return iValue;
}

/*�������ַ��ƫ�Ƽ�����д��ֵ����ֵ���ͣ�ƫ�Ƶ�ַ������*/
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwValue,SIZE_T size,...){
	va_list argptr;
	va_start(argptr,size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,dwBaseAddr,iLevel,size,argptr);
	
	va_end(argptr);
	
	return WriteProcessMemory(hProcess,(LPVOID)finalAddr,(LPVOID)&dwValue,(SIZE_T)size,NULL);
}
