#include "headgr.h"

DWORD Pid;
HANDLE hProcess=0;
int command;

bool isRun=false;
bool backStageRun=false;
bool anyPosition=false;
bool isLittle=false; 

/*������*/
int main(void){
	initModifier();
	
	while(true){
		menu();
		setColor(14);
		
		printf("\n�밴�°���ѡ��ѡ�");
		command=getchar();
		Choice();
	}
	
	return 0;
}
