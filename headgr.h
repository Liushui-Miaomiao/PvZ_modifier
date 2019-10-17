#define DEBUG 0
#define PROCESS_NAME "PlantsVsZombies.exe"
#define BRIGHT_RED FOREGROUND_RED|FOREGROUND_INTENSITY
#define BRIGHT_GREEN FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define BRIGHT_BLUE FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define BRIGHT_YELLOW FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define BRIGHT_MAGENTA FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define BRIGHT_CYAN FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define BRIGHT_WHITE FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define MAGENTA FOREGROUND_RED|FOREGROUND_BLUE

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>

/*p_op - Process Operation*/
BOOL findProcessPidByName(const char cProcessName[],DWORD &dwPid);
void setColor(WORD wColor);
void close(void);

/*pm_op - Process Memory Operation*/
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,SIZE_T size,...);
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwValue,SIZE_T size,...);

/*g_msg - Game Message*/
void menu(void);
void upDate(void);
void cheatCode(void);
void showMiniGameList(void);
void pause(void);
void noOperation(void);
void about(void);
void cheatMsg(BOOL bIsSuccess,const char cMsg[]);
void showOpenCheat(void);
void showProcessName(const char cMsgFirst[],const char cMsgLast[]);

/*g_op - Game Operation*/
void initModifier(void);
BOOL openGameProcess(void);
BOOL openModifier(void);
void choice(void);
int limit(int iValue,int iMin,int iMax);
