#include "headgr.h"

DWORD Pid;
HANDLE hProcess=0;
int command;

BOOL isRun=FALSE;
BOOL backStageRun=FALSE;
BOOL anyPosition=FALSE;
BOOL isLittle=FALSE; 

/*主函数*/
int main(void){
	initModifier();
	
	while(TRUE){
		menu();
		setColor(14);
		
		printf("\n请按下按键选择选项：");
		command=getchar();
		Choice();
	}
	
	return 0;
}
