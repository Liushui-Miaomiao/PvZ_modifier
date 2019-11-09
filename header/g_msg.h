#ifndef _G_MSG_H_
#define _G_MSG_H_

#include "public\headergr.h"

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

#endif
