/*Process Operation*/

#include "headgr.h"

/*ͨ������������pid*/
BOOL findProcessPidByName(const char cProcessName[],DWORD &dwPid){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE){
		return FALSE;
	}
	
	pe32.dwSize=sizeof(PROCESSENTRY32);
	
	if(Process32First(hProcessSnap,&pe32)==0){
		CloseHandle(hProcessSnap);
		return FALSE;
	}
	
	BOOL bRet=FALSE;
	do{
		if(strcmp(cProcessName,pe32.szExeFile)==0){
			dwPid=pe32.th32ProcessID;
			bRet=TRUE;
			break;
		}
	}while(Process32Next(hProcessSnap,&pe32));
	
	CloseHandle(hProcessSnap);
	
	return bRet;
}

/*�ÿ���̨��ɫ*/
void setColor(WORD wColor){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
}

/*�˳�����*/
void close(void){
	exit(EXIT_SUCCESS);
}
