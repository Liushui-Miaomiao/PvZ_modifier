#include "headgr.h"

char processName[]="PlantsVsZombies.exe";
DWORD Pid;
HANDLE hProcess=0;
int command;

BOOL isRun=FALSE;
BOOL backStage=TRUE;
BOOL anyPosition=FALSE;
BOOL isLittle=FALSE; 

/*������*/
int main(void){
	//�ó������
	SetConsoleTitle("��ֲ���ս��ʬ�� C�����޸��� v0.22");
	//�����Ϸ����
	isRun=openGameProcess();
	
	while(TRUE){
		menu();
		setColor(14);
		
		printf("\n�밴�°���ѡ��ѡ�");
		command=getchar();
		Choice();
	}
	
	return 0;
}
