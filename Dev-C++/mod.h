#include <windows.h>
#include <tlhelp32.h>

//���ݽ�������Ѱ�Ҿ�� 
BOOL FindProcessPid(LPCSTR ProcessName, DWORD &dwPid){
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	
	//��ȡϵͳ�����н��̵Ŀ��ա�
	hProcessSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
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

/****************�ڴ����****************/

//�õ�һ��ƫ�Ƶ�ַ 
DWORD getMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//ƫ��1
	DEV_1=BaseAddr+DEV_1;//���յ�ַ
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_1,&value,(SIZE_T)Size,NULL);
		printf("һ��ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",DEV_1,value);
	#endif
	
	return DEV_1;
}

//�õ�����ƫ�Ƶ�ַ 
DWORD getMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//ƫ��1
	ReadProcessMemory(hP,(LPVOID)(BaseAddr+DEV_1),&DEV_1,(SIZE_T)Size,NULL);//ƫ��2
	DEV_2=DEV_1+DEV_2;//���յ�ַ
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_2,&value,(SIZE_T)Size,NULL);
		printf("����ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",DEV_2,value);
	#endif
	
	return DEV_2;
}

//�õ�����ƫ�Ƶ�ַ 
DWORD getMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,SIZE_T Size){
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&BaseAddr,(SIZE_T)Size,NULL);//ƫ��1
	ReadProcessMemory(hP,(LPVOID)(BaseAddr+DEV_1),&DEV_1,(SIZE_T)Size,NULL);//ƫ��2
	ReadProcessMemory(hP,(LPVOID)(DEV_1+DEV_2),&DEV_2,(SIZE_T)Size,NULL);//ƫ��3
	DEV_3=DEV_2+DEV_3;//���յ�ַ 
	
	#if isDebug
		DWORD value;
		ReadProcessMemory(hP,(LPVOID)DEV_3,&value,(SIZE_T)Size,NULL);
		printf("����ƫ�Ƶ�ַΪ��%x����ȡ��ֵΪ��%d\n",DEV_3,value);
	#endif
	
	return DEV_3;
}

/****************�ϻ�ȡ �¶�ȡ****************/

//��ַ������ȡ����ֵ
DWORD readMemory(HANDLE hP,DWORD BaseAddr,SIZE_T Size){
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)BaseAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//��ַ��һ��ƫ�ƣ�����ȡ����ֵ
DWORD readMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_1(hP,BaseAddr,DEV_1,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//��ַ��һ��ƫ�ƣ�����ƫ�ƣ�����ȡ����ֵ
DWORD readMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_2(hP,BaseAddr,DEV_1,DEV_2,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

//��ַ��һ��ƫ�ƣ�����ƫ�ƣ�����ƫ�ƣ�����ȡ����ֵ
DWORD readMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_3(hP,BaseAddr,DEV_1,DEV_2,DEV_3,Size);
	
	DWORD Num;
	ReadProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL);
	return Num;
}

/****************�϶�ȡ ��д��****************/

//��ַ�����޸ĵ���ֵ
DWORD writeMemory(HANDLE hP,DWORD BaseAddr,DWORD Num,SIZE_T Size){
	if(WriteProcessMemory(hP,(LPVOID)BaseAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//��ַ��һ��ƫ�ƣ����޸ĵ���ֵ
DWORD writeMemory_1(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_1(hP,BaseAddr,DEV_1,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//��ַ��һ��ƫ�ƣ�����ƫ�ƣ����޸ĵ���ֵ
DWORD writeMemory_2(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_2(hP,BaseAddr,DEV_1,DEV_2,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}

//��ַ��һ��ƫ�ƣ�����ƫ�ƣ�����ƫ�ƣ����޸ĵ���ֵ
DWORD writeMemory_3(HANDLE hP,DWORD BaseAddr,DWORD DEV_1,DWORD DEV_2,DWORD DEV_3,DWORD Num,SIZE_T Size){
	DWORD finalAddr; 
	finalAddr=getMemory_3(hP,BaseAddr,DEV_1,DEV_2,DEV_3,Size);
	
	if(WriteProcessMemory(hP,(LPVOID)finalAddr,&Num,(SIZE_T)Size,NULL)){
		return 1;
	}else{
		return 0;
	}
}
