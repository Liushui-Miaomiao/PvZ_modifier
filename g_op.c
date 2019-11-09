/*Game Operation*/

#include "header\g_op.h"
#include "header\g_msg.h"
#include "header\pm_op.h"
#include "header\p_op.h"
#include "header\public\color.h"

#include <conio.h>

static DWORD g_dwPid;
static HANDLE g_hProcess;
static int g_iCommand;

static DWORD *p_g_dwBuffer;

/*��ʼ���޸���*/
void initModifier(void){
	SetConsoleTitle("��ֲ���ս��ʬ�� C�����޸��� v0.22");
	
	p_g_dwBuffer=(DWORD *)malloc(sizeof(DWORD));
	
	g_hProcess=0;
	g_bIsBackStageRun=FALSE;
	g_bIsAnyPosition=FALSE;
	g_bIsLittleZombie=FALSE;
	g_bIsRun=openGameProcess();
}

/*ѭ���¼�*/
void loopEvent(void){
	menu();
	setColor(BRIGHT_YELLOW);
	
	printf("\n�밴�°���ѡ��ѡ�");
	g_iCommand=getchar();
	choice();
}

/*����Ϸ����*/
BOOL openGameProcess(void){
	setColor(BRIGHT_YELLOW);
	printf("���ڴ򿪽���...\n");
	
	if(getProcessPidByName(PROCESS_NAME,g_dwPid)){
		showProcessName("[","]");
		printf("[Pid��%d]\n",g_dwPid);
		
		g_hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,g_dwPid);
		
		if (g_hProcess!=0){
			setColor(BRIGHT_GREEN);
			showProcessName("\n�ɹ�����Ϸ����[","]��");
			printf("���̾����%d\n",g_hProcess);
			
			if(readMemory(g_hProcess,0x42748E,4,0)==0xFF563DE8){
				if(readMemory(g_hProcess,0x0054EBEF,1,0)==0xFF563DC3){
					g_bIsBackStageRun=TRUE;
				}
				if(readMemory(g_hProcess,0x0040FE30,1,0)==0xFF563D81&&
				readMemory(g_hProcess,0x00438E40,1,0)==0xFF563DEB&&
				readMemory(g_hProcess,0x0042A2D9,1,0)==0xFF563D8D){
					
					g_bIsAnyPosition=TRUE;
				}
				if(readMemory(g_hProcess,0x00523ED5,1,0)==0xFF563DEB){
					g_bIsLittleZombie=TRUE;
				}
				
				return TRUE;
			}else{
				setColor(BRIGHT_YELLOW);
				puts("\n��֧�ֵ���Ϸ�汾��");
				return FALSE;
			}
		}else{
			setColor(BRIGHT_RED);
			showProcessName("\n����Ϸ����[","]ʧ�ܣ�\n");
		}
	}else{
		setColor(BRIGHT_YELLOW);
		showProcessName("δ�ҵ���Ϸ���̣�","\n");
	}
	
	return FALSE;
}

/*�Ƿ��Ѿ���ȡ��Ϸ����*/
BOOL openModifier(void){
	if(!g_bIsRun){
		setColor(BRIGHT_YELLOW);
		printf("\n���ȴ��޸���������Ϸ�����\n");
	}
	
	return g_bIsRun;
}

/*ѡ������*/
void choice(void){
	setColor(BRIGHT_MAGENTA);
	/*�����ж�*/
	switch(g_iCommand){
		case 'O':
			g_bIsRun=openGameProcess();
			
			pause();
			break;
		#if DEBUG
			case 'T':
				if(openModifier()){
					
				}
				break;
		#endif
		
		/*�����޸�*/
		case 'a':
			choiceBranch("�����޸�");
			break;
		
		/*�ؿ��޸�*/
		case 'b':
			choiceBranch("�ؿ��޸�");
			break;
		
		/*ֲ���޸�*/
		case 'c':
			choiceBranch("ֲ���޸�");
			break;
		
		/*��ʬ�޸�*/
		case 'd':
			choiceBranch("��ʬ�޸�");
			break;
		
		/*��԰�޸�*/
		case 'e':
			choiceBranch("��԰�޸�");
			break;
		
		/*�����޸�*/
		case 'f':
			choiceBranch("�����޸�");
			break;
		case '~':
			upDate();
			break;
		case '!':
			showMiniGameList();
			break;
		case '@':
			cheatCode();
			break;
		case '#':
			showOpenCheat();
			break;
		case 'A':
			about();
			break;
		case 'E':
			close();
			break;
		default :
			noOperation();
	}
	
	/*�ݻ�����*/
	getchar();
}

/*ѡ���֧*/
void choiceBranch(const char branceName[]){
	if(!openModifier()){
		pause();
		return;
	}
	
	getchar();
	setColor(BRIGHT_YELLOW);
	printf("\n�ѽ��롾%s���˵�����ѡ����ѡ�",branceName);
	g_iCommand=getchar();
	setColor(BRIGHT_MAGENTA);
	
	if(!strcmp(branceName,"�����޸�")){
		choiceBranchNormal();
	}else if(!strcmp(branceName,"�ؿ��޸�")){
		choiceBranchLevel();
	}else if(!strcmp(branceName,"ֲ���޸�")){
		choiceBranchPlant();
	}else if(!strcmp(branceName,"��ʬ�޸�")){
		choiceBranchZombie();
	}else if(!strcmp(branceName,"��԰�޸�")){
		choiceBranchGarden();
	}else{
		choiceBranchOther();
	}
}

/*ѡ���֧ - �����޸�*/
void choiceBranchNormal(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵ�����������");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeSunlight(),"����");
			}
			break;
		case '2':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵĽ�Ǯ������");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeMoney(),"��Ǯ");
			}
			break;
		case '3':
			if(openModifier()){
				cheatMsg(cardNoCD(),"��������ȴ");
			}
			break;
		case '4':
			if(openModifier()){
				cheatMsg(backStageRun(g_bIsBackStageRun?0x57:0xC3),g_bIsBackStageRun?"�ָ���̨":"ȡ����̨");
				g_bIsBackStageRun=!g_bIsBackStageRun;
			}
			break;
		case '5':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵĿ��۸�����1~10����");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeCardsNum(),"���۸���");
			}
			break;
		case '6':
			if(openModifier()){
				cheatMsg(autoCollect(),"�Զ��ռ�����");
			}
			break;
		default :
			noOperation();
	}
}

/*ѡ���֧ - �ؿ��޸�*/
void choiceBranchLevel(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵ�ð�չؿ���������Ҫȥ4-3�ؿ�����ôӦ������43����");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(adventureJumpLevel(),"ð��ģʽ�ؿ�");
			}
			break;
		case '2':
			if(openModifier()){
				puts("\n��Ҫ�Ƚ�������ؿ�Ȼ�����˵���");
				puts("��һ��Ҫ��ô�����������������޸���Ч���������¿�ʼ�������ģʽ�µĴ浵����ע�ⱸ�ݴ浵����");
				puts("�޸Ĺؿ�����Ȼ�������¿�ʼ����������¿�ʼ�Ļ�����������ҹؿ���Ч��");
				printf("������Ҫ�����������ϷID��ID��ͨ����ѯ��!���˵��Ĺؿ����루1~70������");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(miniGameJumpLevel(),"С��Ϸ����");
			}
			break;
		default :
			noOperation();
	}
}

/*ѡ���֧ - ֲ���޸�*/
void choiceBranchPlant(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(anyPosition(g_bIsAnyPosition?0x84:0x81,
				g_bIsAnyPosition?0x74:0xEB,
				g_bIsAnyPosition?0x84:0x8D),
				g_bIsAnyPosition?"ȡ���ص�����":"�����ص�����");
				
				g_bIsAnyPosition=!g_bIsAnyPosition;
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(purpleUnlimit(),"�Ͽ���ֲ������");
			}
			break;
		default :
			noOperation();
	}
}

/*ѡ���֧ - ��ʬ�޸�*/
void choiceBranchZombie(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(killAllZombies(),"��ɱȫ����ʬ");
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(littleZombie(g_bIsLittleZombie?0x74:0xEB),
				g_bIsLittleZombie?"�ر�С��ʬ��Ч":"����С��ʬ��Ч");
				
				g_bIsLittleZombie=!g_bIsLittleZombie;
			}
			break;
		default :
			noOperation();
	}
}

/*ѡ���֧ - ��԰�޸�*/
void choiceBranchGarden(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵ��ǻ����߶ȣ�");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeWisdomTree(),"�ǻ����߶�");
			}
			break;
		case '2':
			if(openModifier()){
				printf("\n������Ҫ�޸ĵ��ɿ���������");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeChocolate(),"�ɿ�������");
			}
			break;
		default :
			noOperation();
	}
}

/*ѡ���֧ - �����޸�*/
void choiceBranchOther(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(vaseFluoro(),"��ƿ͸�ӿ���");
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(showHideMiniGame(),"��ʾ����С��Ϸ");
			}
			break;
		default :
			noOperation();
	}
}

/*�淶���ݷ�Χ*/
int limit(int iValue,int iMin,int iMax){
	if(iValue<iMin){
		return iMin;
	}
	if(iValue>iMax){
		return iMax;
	}
	
	return iValue;
}

/*��ͣ*/
void pause(void){
	setColor(BRIGHT_YELLOW);
	puts("\n���������������");
	
	getch();
}

/*����*/
BOOL changeSunlight(void){
	DWORD dwSunlight;
	dwSunlight=limit(*p_g_dwBuffer,0,9990);
	
	return writeMemory(g_hProcess,0x006A9EC0,dwSunlight,4,2,0x768,0x5560);
}

/*��Ǯ*/
BOOL changeMoney(void){
	DWORD dwMoney;
	dwMoney=limit(*p_g_dwBuffer,0,99999);
	
	return writeMemory(g_hProcess,0x006A9EC0,dwMoney,4,2,0x82C,0x28);
}

/*��������ȴ*/
BOOL cardNoCD(void){
	return writeMemory(g_hProcess,0x00487296,0x1477,2,0);
}

/*��̨����*/
BOOL backStageRun(DWORD dwValue){
	return writeMemory(g_hProcess,0x0054EBEF,dwValue,1,0);
}

/*���۸���*/
BOOL changeCardsNum(void){
	DWORD dwCardNum;
	dwCardNum=limit(*p_g_dwBuffer,1,10);
	
	return writeMemory(g_hProcess,0x006A9EC0,dwCardNum,4,3,0x768,0x144,0x24);
}

/*�Զ��ռ�*/
BOOL autoCollect(void){
	return writeMemory(g_hProcess,0x0043158F,0xEB,1,0);
}

/*ð������*/
BOOL adventureJumpLevel(void){
	DWORD dwLevel;
	dwLevel=limit(*p_g_dwBuffer,11,99)-10;
	
	return writeMemory(g_hProcess,0x006A9EC0,dwLevel,4,2,0x82C,0x24);
}

/*С��Ϸ����*/
BOOL miniGameJumpLevel(void){
	DWORD dwLevel;
	dwLevel=limit(*p_g_dwBuffer,1,70);
	
	return writeMemory(g_hProcess,0x006A9EC0,dwLevel,4,1,0x7F8);
}

/*�ص�����*/
BOOL anyPosition(DWORD dwValue_1,DWORD dwValue_2,DWORD dwValue_3){
	return writeMemory(g_hProcess,0x0040FE30,dwValue_1,1,0)&&
		writeMemory(g_hProcess,0x00438E40,dwValue_2,1,0)&&
		writeMemory(g_hProcess,0x0042A2D9,dwValue_3,1,0);
}

/*�Ͽ�������*/
BOOL purpleUnlimit(void){
	return writeMemory(g_hProcess,0x0041D7D0,0xC301B0,3,0)&&
		writeMemory(g_hProcess,0x0040E477,0xEB,1,0);
}

/*��ɱȫ����ʬ*/
BOOL killAllZombies(void){
	int i;
	BOOL bKill=FALSE;
	printf("��ʬ������%d\n",readMemory(g_hProcess,0x006A9EC0,4,2,0x768,0xA0));
	for(i=0;i<ZOMBIES_MAX_NUM;i++){
		if(readMemory(g_hProcess,0x006A9EC0,4,3,0x768,0x90,i*0x15C+0xEC)==ZOMBIES_NORMAL_STATUS){
			bKill=writeMemory(g_hProcess,0x006A9EC0,ZOMBIES_DIE_STATUS,4,3,0x768,0x90,i*0x15C+0x28);
		}
	}
	
	return bKill;
}

/*С��ʬ��Ч*/
BOOL littleZombie(DWORD dwValue){
	return writeMemory(g_hProcess,0x00523ED5,dwValue,1,0);
}

/*�ǻ���*/
BOOL changeWisdomTree(void){
	DWORD dwTreeHigh;
	dwTreeHigh=limit(*p_g_dwBuffer,0,2147483647);
	
	return writeMemory(g_hProcess,0x006A9EC0,dwTreeHigh,4,2,0x82C,0xF4);
}

/*�ɿ���*/
BOOL changeChocolate(void){
	DWORD dwChocolate;
	dwChocolate=limit(*p_g_dwBuffer,0,999)+1000;
	
	return writeMemory(g_hProcess,0x006A9EC0,dwChocolate,4,2,0x82C,0x228);
}

/*��ƿ͸��*/
BOOL vaseFluoro(void){
	return writeMemory(g_hProcess,0x0044E5CC,0x0033B866,4,0);
}

/*��ʾ����С��Ϸ*/
BOOL showHideMiniGame(void){
	return writeMemory(g_hProcess,0x0042DF5D,0x38,1,0);
}