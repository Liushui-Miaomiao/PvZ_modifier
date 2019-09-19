#include "headgr.h"

DWORD Pid;
HANDLE hProcess=0;
int command;

bool isRun=false;
bool backStageRun=false;
bool anyPosition=false;
bool isLittle=false; 

/*主函数*/
int main(void){
	initModifier();
	
	while(true){
		menu();
		setColor(14);
		
		printf("\n请按下按键选择选项：");
		command=getchar();
		Choice();
	}
	
	return 0;
}
