/*Process Operation*/

#include "headgr.h"

/*通过进程名返回pid*/
bool FindProcessPid(LPCSTR ProcessName,DWORD &dwPid){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE){
		return false;
	}
	
	pe32.dwSize=sizeof(PROCESSENTRY32);
	
	if(!Process32First(hProcessSnap,&pe32)){
		CloseHandle(hProcessSnap);
		return false;
	}
	
	bool bRet=false;
	do{
		if(strcmp(ProcessName,pe32.szExeFile)==0){
			dwPid=pe32.th32ProcessID;
			bRet=true;
			break;
		}
	}while(Process32Next(hProcessSnap,&pe32));
	
	CloseHandle(hProcessSnap);
	return bRet;
}

/*置控制台颜色*/
void setColor(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

/*退出程序*/
void close(void){
	exit(0);
}
