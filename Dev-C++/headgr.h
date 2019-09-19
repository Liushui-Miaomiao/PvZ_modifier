#define DEBUG 0
#define PROCESS_NAME "PlantsVsZombies.exe" 

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>


/*p_op - Process Operation*/
bool FindProcessPid(LPCSTR ProcessName,DWORD &dwPid);
void setColor(int c);
void close(void);

/*pm_op - Process Memory Operation*/
DWORD readMemory(HANDLE hProcess,DWORD BaseAddr,int level,SIZE_T Size,...);
bool writeMemory(HANDLE hProcess,DWORD BaseAddr,int level,DWORD value,SIZE_T Size,...);

/*g_msg - Game Message*/
void menu(void);
void upData(void);
void cheatCode(void);
void showMiniGameList(void);
void pause(void);
void noOperation(void);
void about(void);
void cheatMsg(bool isSuccess,const char msg[]);
void showOpenCheat(void);
void showProcessName(const char msg1[],const char msg2[]);

/*g_op - Game Operation*/
void initModifier(void);
bool openGameProcess(void);
bool openModify(void);
void Choice(void);
int limit(int value,int min,int max);

