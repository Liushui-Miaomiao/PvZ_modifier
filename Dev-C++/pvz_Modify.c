#include "headgr.h"

char processName[]="PlantsVsZombies.exe";
DWORD Pid;
HANDLE hProcess=0;
int command;

BOOL isRun=FALSE;
BOOL backStage=TRUE;
BOOL anyPosition=FALSE;
BOOL isLittle=FALSE; 

/*主函数*/
int main(void){
	//置程序标题
	SetConsoleTitle("【植物大战僵尸】 C语言修改器 v0.22");
	//检测游戏进程
	isRun=openGameProcess();
	
	while(TRUE){
		menu();
		setColor(14);
		
		printf("\n请按下按键选择选项：");
		command=getchar();
		Choice();
	}
	
	return 0;
}
