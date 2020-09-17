#include "public_header.h"

#include "process.h"
#include "color.h"
#include "memory.h"

#include <tlhelp32.h>
#include <conio.h>

extern char* VERSION;														//��չ_�汾��
extern char* PROCESS_NAME;													//��չ_������

DWORD	g_dwPid;															//ȫ��_��ϷPid
HANDLE	g_hProcess;															//ȫ��_��Ϸ���
BOOL	g_bGameIsRun;														//ȫ��_��Ϸ�Ƿ�������
BOOL	g_bIsBackStageRun;													//ȫ��_�Ƿ������̨����
BOOL	g_bIsAnyPosition;													//ȫ��_�Ƿ�����������ֲ
BOOL	g_bIsLittleZombie;													//ȫ��_�Ƿ�����С��ʬ��Ч
char	title[34] = "[Plants vs. Zombie] modifier ";						//��Ϸ����
DWORD*	p_dwBuffer;															//���뻺����

static void ReadState(void);												//��ȡ״̬

void Init(void) {
	strcat_s(title, sizeof(title), VERSION);
	SetConsoleTitleA(title);

	p_dwBuffer = (DWORD*)malloc(sizeof(DWORD));
	if (p_dwBuffer == NULL) {
		SetColor(BRIGHT_RED);
		puts("���뻺���ڴ����ʧ�ܣ�");

		Pause();
		Close();
	}

	g_hProcess			= 0;
	g_bIsBackStageRun	= FALSE;
	g_bIsAnyPosition	= FALSE;
	g_bIsLittleZombie	= FALSE;
	g_bGameIsRun		= OpenGameProcess();
}

BOOL OpenGameProcess(void) {
	SetColor(BRIGHT_YELLOW);
	printf("���ڴ���Ϸ����[%s]����\n", PROCESS_NAME);

	if (GetProcessPidByName(PROCESS_NAME, &g_dwPid)) {						//����ͨ����������ȡ����PID
		printf("[Pid]:%d\n", g_dwPid);

		g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_dwPid);		//���Դ򿪽���
		if (g_hProcess) {
			SetColor(BRIGHT_GREEN);
			puts("��Ϸ���̴򿪳ɹ���");
			
			ReadState();													//��ȡ��Ϸ����״̬
			return TRUE;
		}
		else {
			SetColor(BRIGHT_RED);
			puts("��Ϸ���̴�ʧ�ܣ�");
		}
	}
	else {
		puts("��Ϸ����δ�ҵ���");
	}

	return FALSE;
}

BOOL GetProcessPidByName(char *cProcessName, DWORD *dwPid) {
	HANDLE l_hProcessSnap;

	l_hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);		//������̿���
	if (l_hProcessSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	PROCESSENTRY32 l_pe32;
	l_pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(l_hProcessSnap, &l_pe32) == 0) {						//��һ�������Ƿ����
		CloseHandle(l_hProcessSnap);
		return FALSE;
	}

	BOOL bIsOK = FALSE;
	do {
		if (!strcmp(cProcessName, l_pe32.szExeFile)) {						//�ȽϽ�����
			*dwPid = l_pe32.th32ProcessID;									//��ȡ����Pid
			bIsOK = TRUE;
			break;
		}
	} while (Process32Next(l_hProcessSnap, &l_pe32));

	CloseHandle(l_hProcessSnap);

	return bIsOK;
}

static void ReadState(void) {
	if (ReadMemory(0x42748E, 4, 0) == 0xFF563DE8) {							//�жϰ汾
		//printf("%d\t%d", ReadMemory(0x0054EBEF, 1, 0), 0xCCCCCCC3);
		if (ReadMemory(0x0054EBEF, 1, 0) == 0xCCCCCCC3) {
			g_bIsBackStageRun = TRUE;
		}//����Ķ���û���Ժ��޸ģ������ٸ�
		if (ReadMemory(0x0040FE30, 1, 0) == 0xFF563D81 &&
			ReadMemory(0x00438E40, 1, 0) == 0xFF563DEB &&
			ReadMemory(0x0042A2D9, 1, 0) == 0xFF563D8D) {

			g_bIsAnyPosition = TRUE;
		}
		if (ReadMemory(0x00523ED5, 1, 0) == 0xFF563DEB) {
			g_bIsLittleZombie = TRUE;
		}
	}
	else {
		SetColor(BRIGHT_YELLOW);
		puts("��֧�ֵİ汾��");
	}
}

void Pause(void) {
	SetColor(BRIGHT_YELLOW);
	puts("\n���������������");

	_getch();
}

void SetColor(WORD wColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void Close(void) {
	if (p_dwBuffer != NULL) {
		free(p_dwBuffer);
	}

	exit(EXIT_SUCCESS);
}