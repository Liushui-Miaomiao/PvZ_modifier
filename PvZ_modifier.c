#include "headgr.h"

DWORD Pid;
HANDLE hProcess=0;
int command;

BOOL isRun=FALSE;
BOOL backStageRun=FALSE;
BOOL anyPosition=FALSE;
BOOL isLittle=FALSE; 

/*������*/
int main(void){
	initModifier();
	
	while(TRUE){
		menu();
		setColor(14);
		
		printf("\n�밴�°���ѡ��ѡ�");
		command=getchar();
		Choice();
	}
	
	return 0;
}
