#include "headgr.h"

DWORD g_dwPid;
HANDLE g_hProcess=0;
int g_iCommand;

BOOL g_bIsRun=FALSE;
BOOL g_bIsBackStageRun=FALSE;
BOOL g_bIsAnyPosition=FALSE;
BOOL g_bIsLittleZombie=FALSE; 

/*������*/
int main(void){
	initModifier();
	
	while(TRUE){
		menu();
		setColor(BRIGHT_YELLOW);
		
		printf("\n�밴�°���ѡ��ѡ�");
		g_iCommand=getchar();
		choice();
	}
	
	return EXIT_FAILURE;
}
