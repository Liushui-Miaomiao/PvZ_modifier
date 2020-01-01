/*Process Operation*/

#include "header\p_op.h"

#include <tlhelp32.h>
#include <stdlib.h>

extern DWORD *p_g_dwBuffer;

/*ͨ������������pid*/
BOOL getProcessPidByName(const char cProcessName[],DWORD &dwPid){
	HANDLE hProcessSnap;
	
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE){
		return FALSE;
	}
	
	PROCESSENTRY32 pe32;
	pe32.dwSize=sizeof(PROCESSENTRY32);
	
	if(!Process32First(hProcessSnap,&pe32)){
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	
	BOOL bIsOK=FALSE;
	do{
		if(!strcmp(cProcessName,pe32.szExeFile)){
			dwPid=pe32.th32ProcessID;
			bIsOK=TRUE;
			break;
		}
	}while(Process32Next(hProcessSnap,&pe32));
	
	CloseHandle(hProcessSnap);
	
	return bIsOK;
}

/*�ÿ���̨��ɫ*/
void setColor(WORD wColor){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}

/*�˳�����*/
void close(void){
	if(p_g_dwBuffer!=NULL){
		free(p_g_dwBuffer);
	}
	exit(EXIT_SUCCESS);
}
