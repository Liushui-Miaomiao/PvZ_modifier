#define DEBUG 0

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>


/*p_op - Process Operation*/
BOOL FindProcessPid(LPCSTR ProcessName,DWORD &dwPid);
void setColor(int c);

/*pm_op - Process Memory Operation*/
DWORD readMemory(HANDLE hProcess,DWORD BaseAddr,int level,SIZE_T Size,...);
BOOL writeMemory(HANDLE hProcess,DWORD BaseAddr,int level,DWORD value,SIZE_T Size,...);

/*g_msg - Game Message*/
void menu(void);
void upData(void);
void cheatCode(void);
void showMiniGameList(void);
void pause(void);
void noOperation(void);
void about(void);
void cheatMsg(BOOL isSuccess,const char msg[]);
void showOpenCheat(void);

/*g_op - Game Operation*/
BOOL openGameProcess(void);
BOOL openModify(void);
void Choice(void);
int limit(int value,int min,int max);

