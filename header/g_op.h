#ifndef _G_OP_H_
#define _G_OP_H_

#define ZOMBIES_MAX_NUM 1024
#define ZOMBIES_NORMAL_STATUS 0
#define ZOMBIES_DIE_STATUS 3

#include "public\headergr.h"

BOOL g_bIsRun;
BOOL g_bIsBackStageRun;
BOOL g_bIsAnyPosition;
BOOL g_bIsLittleZombie;

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

BOOL changeSunlight(void);
BOOL changeMoney(void);
BOOL cardNoCD(void);
BOOL backStageRun(DWORD dwValue);
BOOL changeCardsNum(void);
BOOL autoCollect(void);
BOOL adventureJumpLevel(void);
BOOL miniGameJumpLevel(void);
BOOL anyPosition(DWORD dwValue_1,DWORD dwValue_2,DWORD dwValue_3);
BOOL purpleUnlimit(void);
BOOL killAllZombies(void);
BOOL littleZombie(DWORD dwValue);
BOOL changeWisdomTree(void);
BOOL changeChocolate(void);
BOOL vaseFluoro(void);
BOOL showHideMiniGame(void);

#endif
