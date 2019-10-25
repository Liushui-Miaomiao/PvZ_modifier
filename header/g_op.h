#ifndef _G_OP_H_
#define _G_OP_H_

#define ZOMBIES_MAX_NUM 1024
#define ZOMBIES_NORMAL_STATUS 0
#define ZOMBIES_DIE_STATUS 3

#include "public\headergr.h"
#include "public\color.h"

#include <conio.h>

DWORD g_dwPid;
HANDLE g_hProcess;
int g_iCommand;

BOOL g_bIsRun;
BOOL g_bIsBackStageRun;
BOOL g_bIsAnyPosition;
BOOL g_bIsLittleZombie;

DWORD *p_g_dwBuffer;

/*p_op - Process Operation*/
void close(void);

/*pm_op - Process Memory Operation*/
BOOL getProcessPidByName(const char cProcessName[],DWORD &dwPid);
DWORD readMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwSize,...);
BOOL writeMemory(HANDLE hProcess,DWORD dwBaseAddr,int iLevel,DWORD dwValue,DWORD dwSize,...);

/*g_msg - Game Message*/
void menu(void);
void upDate(void);
void cheatCode(void);
void showMiniGameList(void);
void noOperation(void);
void about(void);
void cheatMsg(BOOL bIsSuccess,const char cMsg[]);
void showOpenCheat(void);
void showProcessName(const char cMsgFirst[],const char cMsgLast[]);

/*g_op - Game Operation*/
void initModifier(void);
void loopEvent(void);
BOOL openGameProcess(void);
BOOL openModifier(void);
void choice(void);
void choiceBranch(const char branceName[]);
void choiceBranchNormal(void);
void choiceBranchLevel(void);
void choiceBranchPlant(void);
void choiceBranchZombie(void);
void choiceBranchGarden(void);
void choiceBranchOther(void);
int limit(int iValue,int iMin,int iMax);
void pause(void);

BOOL changeSunlight(DWORD *p_dwSunlight);
BOOL changeMoney(DWORD *p_dwMoney);
BOOL cardNoCD(void);
BOOL backStageRun(DWORD dwValue);
BOOL changeCardsNum(DWORD *p_dwCardNum);
BOOL autoCollect(void);
BOOL adventureJumpLevel(DWORD *p_dwLevel);
BOOL miniGameJumpLevel(DWORD *p_dwLevel);
BOOL anyPosition(DWORD dwValue_1,DWORD dwValue_2,DWORD dwValue_3);
BOOL purpleUnlimit(void);
BOOL killAllZombies(void);
BOOL littleZombie(DWORD dwValue);
BOOL changeWisdomTree(DWORD *p_dwTreeHigh);
BOOL changeChocolate(DWORD *p_dwChocolate);
BOOL vaseFluoro(void);
BOOL showHideMiniGame(void);

#endif
