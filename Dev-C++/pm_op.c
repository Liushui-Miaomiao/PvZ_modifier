/*Process Memory Operation*/

#include <stdarg.h>
#include "headgr.h"

/*�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������*/
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
		printf("ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",tempAddr,value);
	#endif
	
	return tempAddr;
}

/*�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������*/
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

/*�������ַ��ƫ�Ƽ�����д��ֵ����ֵ���ͣ�ƫ�Ƶ�ַ������*/
BOOL writeMemory(HANDLE hProcess,DWORD BaseAddr,int level,DWORD value,SIZE_T Size,...){
	va_list argptr;
	va_start(argptr,Size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,BaseAddr,level,Size,argptr);
	
	va_end(argptr);
	
	return WriteProcessMemory(hProcess,(LPVOID)finalAddr,&value,(SIZE_T)Size,NULL);
}
