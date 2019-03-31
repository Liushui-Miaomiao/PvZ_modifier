#include <windows.h>
#include <tlhelp32.h>

//根据进程名称寻找句柄 
BOOL FindProcessPid(LPCSTR ProcessName, DWORD &dwPid){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	//获取系统中所有进程的快照。
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap==INVALID_HANDLE_VALUE){
		return(FALSE);
	}
	
	pe32.dwSize=sizeof(PROCESSENTRY32);
	
	if(!Process32First(hProcessSnap,&pe32)){
		//清除快照对象
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
    
    //清除快照对象
	CloseHandle(hProcessSnap);
	return bRet;
}

/****************内存操作****************/

//得到一级偏移地址 
DWORD getMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//偏移1
	DEV_1=BaseAddr+DEV_1;//最终地址
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_1,&value,(SIZE_T)Size,NULL);
		printf("一次偏移地址为：%x，读取的值为：%d\n",DEV_1,value);
	#endif
	
	return DEV_1;
}

//得到二级偏移地址 
DWORD getMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//偏移1
	ReadProcessMemory(hP,(LPVOID)(BaseAddr+DEV_1),&DEV_1,(SIZE_T)Size,NULL);//偏移2
	DEV_2=DEV_1+DEV_2;//最终地址
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_2,&value,(SIZE_T)Size,NULL);
		printf("二次偏移地址为：%x，读取的值为：%d\n",DEV_2,value);
	#endif
	
	return DEV_2;
}

//得到三级偏移地址 
DWORD getMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//偏移1
	ReadProcessMemory(hP,(LPVOID)(BaseAddr+DEV_1),&DEV_1,(SIZE_T)Size,NULL);//偏移2
	ReadProcessMemory(hP,(LPVOID)(DEV_1+DEV_2),&DEV_2,(SIZE_T)Size,NULL);//偏移3
	DEV_3=DEV_2+DEV_3;//最终地址 
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_3,&value,(SIZE_T)Size,NULL);
		printf("三次偏移地址为：%x，读取的值为：%d\n",DEV_3,value);
	#endif
	
	return DEV_3;
}

/****************上获取 下读取****************/

//基址，欲读取的数值
DWORD readMemory(HANDLE hP,DWORD BaseAddr,SIZE_T Size){
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//基址，一级偏移，欲读取的数值
DWORD readMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_1(hP,BaseAddr,DEV_1,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//基址，一级偏移，二级偏移，欲读取的数值
DWORD readMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_2(hP,BaseAddr,DEV_1,DEV_2,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//基址，一级偏移，二级偏移，三级偏移，欲读取的数值
DWORD readMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_3(hP,BaseAddr,DEV_1,DEV_2,DEV_3,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

/****************上读取 下写入****************/

//基址，欲修改的数值
DWORD writeMemory(HANDLE hP,DWORD BaseAddr,DWORD Num,SIZE_T Size){
	if(WriteProcessMemory(hP,(LPVOID)BaseAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//基址，一级偏移，欲修改的数值
DWORD writeMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_1(hP,BaseAddr,DEV_1,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//基址，一级偏移，二级偏移，欲修改的数值
DWORD writeMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_2(hP,BaseAddr,DEV_1,DEV_2,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//基址，一级偏移，二级偏移，三级偏移，欲修改的数值
DWORD writeMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_3(hP,BaseAddr,DEV_1,DEV_2,DEV_3,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}
