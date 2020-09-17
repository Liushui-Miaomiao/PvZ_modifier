#include "public_header.h"

#include "process.h"
#include "color.h"
#include "memory.h"

#include <tlhelp32.h>
#include <conio.h>

extern char* VERSION;														//扩展_版本号
extern char* PROCESS_NAME;													//扩展_进程名

DWORD	g_dwPid;															//全局_游戏Pid
HANDLE	g_hProcess;															//全局_游戏句柄
BOOL	g_bGameIsRun;														//全局_游戏是否运行中
BOOL	g_bIsBackStageRun;													//全局_是否允许后台运行
BOOL	g_bIsAnyPosition;													//全局_是否允许任意种植
BOOL	g_bIsLittleZombie;													//全局_是否允许小僵尸特效
char	title[34] = "[Plants vs. Zombie] modifier ";						//游戏标题
DWORD*	p_dwBuffer;															//输入缓冲区

static void ReadState(void);												//读取状态

void Init(void) {
	strcat_s(title, sizeof(title), VERSION);
	SetConsoleTitleA(title);

	p_dwBuffer = (DWORD*)malloc(sizeof(DWORD));
	if (p_dwBuffer == NULL) {
		SetColor(BRIGHT_RED);
		puts("输入缓冲内存分配失败！");

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
	printf("正在打开游戏进程[%s]……\n", PROCESS_NAME);

	if (GetProcessPidByName(PROCESS_NAME, &g_dwPid)) {						//尝试通过进程名获取进程PID
		printf("[Pid]:%d\n", g_dwPid);

		g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_dwPid);		//尝试打开进程
		if (g_hProcess) {
			SetColor(BRIGHT_GREEN);
			puts("游戏进程打开成功！");
			
			ReadState();													//读取游戏现有状态
			return TRUE;
		}
		else {
			SetColor(BRIGHT_RED);
			puts("游戏进程打开失败！");
		}
	}
	else {
		puts("游戏进程未找到！");
	}

	return FALSE;
}

BOOL GetProcessPidByName(char *cProcessName, DWORD *dwPid) {
	HANDLE l_hProcessSnap;

	l_hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);		//拍摄进程快照
	if (l_hProcessSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	PROCESSENTRY32 l_pe32;
	l_pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(l_hProcessSnap, &l_pe32) == 0) {						//第一个进程是否存在
		CloseHandle(l_hProcessSnap);
		return FALSE;
	}

	BOOL bIsOK = FALSE;
	do {
		if (!strcmp(cProcessName, l_pe32.szExeFile)) {						//比较进程名
			*dwPid = l_pe32.th32ProcessID;									//获取进程Pid
			bIsOK = TRUE;
			break;
		}
	} while (Process32Next(l_hProcessSnap, &l_pe32));

	CloseHandle(l_hProcessSnap);

	return bIsOK;
}

static void ReadState(void) {
	if (ReadMemory(0x42748E, 4, 0) == 0xFF563DE8) {							//判断版本
		//printf("%d\t%d", ReadMemory(0x0054EBEF, 1, 0), 0xCCCCCCC3);
		if (ReadMemory(0x0054EBEF, 1, 0) == 0xCCCCCCC3) {
			g_bIsBackStageRun = TRUE;
		}//下面的都还没测试和修改，后面再改
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
		puts("不支持的版本！");
	}
}

void Pause(void) {
	SetColor(BRIGHT_YELLOW);
	puts("\n按任意键继续……");

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