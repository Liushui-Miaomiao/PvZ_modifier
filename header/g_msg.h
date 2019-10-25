#ifndef _G_MSG_H_
#define _G_MSG_H_

#include "public\headergr.h"
#include "public\color.h"

extern BOOL g_bIsRun;
extern BOOL g_bIsBackStageRun;
extern BOOL g_bIsAnyPosition;
extern BOOL g_bIsLittleZombie;

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
void pause(void);

#endif
