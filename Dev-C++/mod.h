#include <windows.h>
#include <tlhelp32.h>
#include <stdarg.h> 

//���ݽ�������Ѱ�Ҿ��
BOOL FindProcessPid(LPCSTR ProcessName,DWORD &dwPid){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	//��ȡϵͳ�����н��̵Ŀ���
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProcessSnap==INVALID_HANDLE_VALUE){
		return(FALSE);
	}
	
	pe32.dwSize=sizeof(PROCESSENTRY32);
	
	if(!Process32First(hProcessSnap,&pe32)){
		//������ն���
		CloseHandle(hProcessSnap);
		return(FALSE);
	}
	
	BOOL bRet=FALSE;
	do{
		if(!strcmp(ProcessName,pe32.szExeFile)){
			dwPid=pe32.th32ProcessID;
			bRet=TRUE;
			break;
		}
	}while(Process32Next(hProcessSnap,&pe32));
	
	//������ն���
	CloseHandle(hProcessSnap);
	return bRet;
}

//�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������
DWORD getMemory(HANDLE hProcess,DWORD BaseAddr,int level,SIZE_T Size,va_list argptr){
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

//�������ַ��ƫ�Ƽ�������ֵ���ͣ�ƫ�Ƶ�ַ������
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

//�������ַ��ƫ�Ƽ�����д��ֵ����ֵ���ͣ�ƫ�Ƶ�ַ������
DWORD writeMemory(HANDLE hProcess,DWORD BaseAddr,int level,DWORD value,SIZE_T Size,...){
	va_list argptr;
	va_start(argptr,Size);
	
	DWORD finalAddr;
	finalAddr=getMemory(hProcess,BaseAddr,level,Size,argptr);
	
	va_end(argptr);
	
	return WriteProcessMemory(hProcess,(LPVOID)finalAddr,&value,(SIZE_T)Size,NULL);
}
