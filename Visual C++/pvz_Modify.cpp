/*ֲ���ս��ʬC�����޸���*/

//�Ƿ�Ϊ���԰汾
#define isDebug 0

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "mod.h"

//��Ϸ�������� 
char processName[]="PlantsVsZombies.exe";
//���ڻ�ȡ����������ַ�
char Command;
//�������PID
DWORD Pid;
//����ȫ�ֽ��̾��
HANDLE hProcess=0;
//�����Ƿ��Ѿ�����
int isPro=0; 
//�Ƿ��̨���б�ʶ
int backStage=1;

//Timer
static BOOL TimerIsRun;
static BOOL TimerIsExit;
static DWORD TimerDelay;

/*��������*/
int openPro();
int openMod();
void menu();
void Choice();
void cheatMsg(int isSuccess,const char msg[10]);
void pause();
void showMiniGameList();
void cheatCode();
void TimerThread();
void color(int c);

/*������*/
int main(){
	//���ó������ 
	SetConsoleTitle("ֲ���ս��ʬ C�����޸��� v0.1");
	//�����Ϸ����
	isPro=openPro();
	
	while(1){
		menu();
		color(14);
		printf("\n�밴�°���������Ӧ������");
		//����������ַ� 
		Command=getchar();
		Choice();
		//�ݻ����� 
		getchar();
	}
	return 0;
}

//�򿪽���
int openPro(){
	color(14);
	printf("���ڴ򿪽���...\n");
	
	//Ѱ�ҽ������Ʋ�����pid 
	if(FindProcessPid(processName,Pid)){
		printf("[%s][Pid��%d]\n",processName,Pid);
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if (hProcess!=0){
			color(10);
			printf("\n�ɹ�����Ϸ����[%s]�����̾����%d\n",processName,hProcess);
			return 1;
		}else{
			color(12);
			printf("\n����Ϸ����[%s]ʧ��\n",processName);
		}
	}else{
		color(14);
		printf("δ�ҵ���Ϸ���̣�%s\n",processName);
	}
	return 0;
}

//�޸����Ƿ��Ѿ�������Ϸ���� 
int openMod(){
	if(hProcess==0){
		color(14);
		printf("\n���ȴ��޸���������Ϸ�����\n");
		return 0;
	}
	return 1;
}

//���˵� 
void menu(){
	color(15);
	printf("\n����������������������������������������\n");
	printf("ֲ���ս��ʬC�����޸���\n\n");
	printf("O�����´�/��������[%s]\n",processName);
	if(isPro){
		#if isDebug
			printf("T�����Դ��루Debug��\n");
		#endif
		printf("1���޸�����\n");
		printf("2���޸Ľ�Ǯ\n");
		printf("3������ȫ������ȴʱ��\n");
		printf("4���޸��ǻ����߶�\n");
		printf("5���޸�ֲ�￨�۸���\n");
		printf("6��ð��ģʽ����\n");
		printf("7��С��Ϸ����\n");
		printf("8�������̨���У��ٿ�һ��ȡ����\n");
		printf("9����ɱ�������н�ʬ����̫�ȶ���\n");
		printf("0����ƿ͸�ӣ����˳��ҹ���ģʽ���޸��̻߳��Զ��˳���\n");
	}
	printf("\n���⹦�ܣ�\n");
	printf("�����鿴����С��Ϸ������ģʽ������ģʽ�ؿ�����\n");
	printf("@���鿴PVZ�����루�ʵ�����ȫ\n");
	printf("A�����ڱ��޸�����Ϣ\n");
	printf("\nE���˳��޸���");
	printf("\n����������������������������������������\n");
}

//�ж�ѡ��
void Choice(){
	color(13);
	//�����ַ��ж�Ӧ��ִ��ʲô���� 
	switch(Command){
		case 'E':
			exit(0);
			break;
		case 'O':
			isPro=openPro();
			break;
		#if isDebug
		case 'T':
			if(openMod()){
				printf("\n��ǰֵΪ��");
				writeMod_3(hProcess,0x006A9EC0,0x768,0x90,0x15C+0x28,3,4);
			}
			break;
		#endif
		case '1':
			if(openMod()){
				DWORD Sun;
				printf("\n������Ҫ�޸ĵ�����������");
				scanf("%d",&Sun);
				if(Sun<0)Sun=0;
				if(Sun>9990)Sun=9990;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x768,0x5560,Sun,4),"����");
			}
			break;
		case '2':
			if(openMod()){
				DWORD Money;
				printf("\n������Ҫ�޸ĵĽ�Ǯ������");
				scanf("%d",&Money);
				if(Money<0)Money=0;
				if(Money>99999)Money=99999;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x28,Money,4),"��Ǯ");
			}
			break;
		case '3':
			if(openMod()){
				DWORD notCoolNum=0x1477;
				cheatMsg(WriteProcessMemory(hProcess,(LPVOID)0x00487296,&notCoolNum,2,NULL),"��������ȴ");
			} 
			break;
		case '4':
			if(openMod()){
				DWORD Tree;
				printf("\n������Ҫ�޸ĵ��ǻ����߶ȣ�");
				scanf("%d",&Tree);
				if(Tree<0)Tree=0;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0xF4,Tree,4),"�ǻ����߶�");
			}
			break;
		case '5':
			if(openMod()){
				DWORD Card;
				printf("\n������Ҫ�޸ĵĿ��۸�����1~10����");
				scanf("%d",&Card);
				if(Card<1)Card=1;
				if(Card>10)Card=10;
				cheatMsg(writeMod_3(hProcess,0x006A9EC0,0x768,0x144,0x24,Card,4),"���۸���");
			}
			break;
		case '6':
			if(openMod()){
				DWORD Checkpoint;
				printf("\n������Ҫ�޸ĵ�ð�չؿ���������Ҫȥ4-3�ؿ�����ôӦ������43����");
				scanf("%d",&Checkpoint);
				if(Checkpoint<11)Checkpoint=11;
				Checkpoint-=10;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x24,Checkpoint,4),"ð��ģʽ�ؿ�");
			}
			break;
		case '7':
			if(openMod()){
				DWORD MiniGame;
				printf("\n��Ҫ�Ƚ�������ؿ�Ȼ�����˵���һ��Ҫ��ô�����������������޸���Ч���������¿�ʼ�������ģʽ�µĴ浵����ע�ⱸ�ݴ浵�����޸Ĺؿ�����Ȼ�������¿�ʼ\n"); 
				printf("������Ҫ�����������ϷID��ID��ͨ����ѯ�������˵��Ĺؿ����루1~70������");
				scanf("%d",&MiniGame);
				if(MiniGame<1)MiniGame=1;
				if(MiniGame>70)MiniGame=70;
				cheatMsg(writeMod_1(hProcess,0x006A9EC0,0x7F8,MiniGame,4),"С��Ϸ����");
			}
			break;
		case '8':
			if(openMod()){
				DWORD cancelBackstage=0xc3;
				(backStage==1)?(cancelBackstage=0xC3):(cancelBackstage=0x57);
				cheatMsg(writeMod(hProcess,0x0054EBEF,cancelBackstage,1),backStage==1?"ȡ����̨":"�ָ���̨");
				backStage=!backStage;
			}
			break;
		case '9':
			if(openMod()){
				int zombieNum;
				ReadProcessMemory(hProcess,(LPCVOID)getMemory_2(hProcess,0x006A9EC0,0x768,0xA0,4),&zombieNum,4,NULL);
				int z_i;
				int kill=0;
				for(z_i=0;z_i<zombieNum;z_i++){
					kill=writeMod_3(hProcess,0x006A9EC0,0x768,0x90,z_i*0x15C+0x28,3,4);
				}
				cheatMsg(kill,"��ɱȫ����ʬ");
			}
			break;
		case '0':
			if(openMod()){
				int sign;
				//�ȶ�ȡ��ƿ�����������0�������ж�ʧ�ܣ�����ʧ����� 
				sign=ReadProcessMemory(hProcess,(LPVOID)getMemory_3(hProcess,0x006A9EC0,0x768,0x11C,0x4C,4),&sign,4,0);
				if(sign!=0){
					HANDLE hTimerThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TimerThread,NULL,0,NULL);
					if(!hTimerThread){
						color(12);
						fprintf(stderr,"\n�޸��̴߳���ʧ�ܣ�\n");
						pause();
					}
					//Timer���м�� 
					TimerDelay=100;
				}
				cheatMsg(sign,"��ƿ͸�ӿ���");
			}
			break;
		//~
		/*case '\x7E':
			if(openMod()){
				int zombieNum;
				
				printf("\n��ǰ��ʬ����Ϊ��%d\n",zombieNum);
			}
			break;*/
		//!
		case '\x21':
			showMiniGameList();
			break;
		//@
		case '\x40':
			cheatCode();
			break;
		case 'A':
			printf("\n���ڣ���������ֲ���ս��ʬ��PlantsVsZombies�����޸�����ʹ��Visual C++��������\n�޸������ߣ���ˮ������\n��л��ҵ�ʹ�ã����κ����ʺ�bug���Է������ҡ�\n\n");
			pause();
			break;
		default :
			color(14);
			printf("\n�Ҳ�����ز������������������������\n");
	}
} 

//�޸���Ϣ 
void cheatMsg(int isSuccess,const char msg[10]){
	if(isSuccess){
		color(10);
		printf("\n�޸�%s�ɹ���\n",msg);
	}else{
		color(12);
		printf("\n�޸�%sʧ�ܣ�\n",msg);
	}
	pause();
}

//��ͣ���� 
void pause(){
	color(14);
	printf("\n���������������\n");
	getch();
} 

//������Ϸ���� 
void showMiniGameList(){
	color(11);
	printf("\nС��Ϸ����\n\n");
	const char *MiniGame[]={"����ģʽ������","����ģʽ����ҹ","����ģʽ��Ӿ��","����ģʽ��Ũ��","����ģʽ���ݶ�",
							"����ģʽ�����죨���ѣ�","����ģʽ����ҹ�����ѣ�","����ģʽ��Ӿ�أ����ѣ�","����ģʽ��Ũ�����ѣ�","����ģʽ���ݶ������ѣ�",
							"����ģʽ�����죨�޾���","����ģʽ����ҹ���޾���","����ģʽ��Ӿ�أ��޾���","����ģʽ��Ũ���޾���","����ģʽ���ݶ����޾���",
							"ֲ�ｩʬ","���������ģʽ","�ϻ���","������ֲ��","��ʯ����",
							"����ʳ����","������","��ʬˮ���","��ʯ����תת��","С��ʬ���鷳",
							"����������","�㿴������������һ��","ѩ����","��ʬ����","����ʬ",
							"˭Ц�����","ֲ�ｩʬ2","���������2","�������","������ʿ�ĸ���", 
							"�������������������","����","�޲�Ƥ֮�أ�����������ԭ����2����Ƥ��","��Ҫʱ��","��ս��̫����������",
							"��Ϯ","�����ؿ�","������԰������������","����Ѱ���ĵ�������","��Ĺģʽ",
							"���ܰ����ڳ�����","�ڰ��ı�����ҹ","�ļ�����ս","����","�ǻ���������������",
							"�ƹ���","ȫ������","����������","������Ӧ","M����˼�ǽ���",
							"���ӵ����չ�","��Ϸ��","��һ��������Ӧ","��������","�޾�������",
							"���ǽ�ʬ","��Ҳ�ǽ�ʬ","���ܲ�����ô","��ȫɵ��","������ͧ",
							"������","��ʬҡ��","������","������д��Զ��������ҵ�","���ǽ�ʬ�޾���"
	};
	
	int gameLen=sizeof(MiniGame)/sizeof(MiniGame[0]);
	int i;
	for(i=0;i<gameLen;i++){
		//��ǳ���ؿ�
		if(i==37||i==42||i==49){
			color(12);
			printf("*");
		}else{
			color(11);
		} 
		printf("%d.%s\n",i+1,MiniGame[i]);
	}
	
	pause();
}

//������ 
void cheatCode(){
	color(5);
	printf("\nPVZ�������ȫ�������ǻ�����һ���߶��ǻ����������ģ�\n\n");
	printf("future ------ ��ʬ����ʱ��̫���۾�\n");
	printf("mustache ---- ��ʬ������Ʋ����\n");
	printf("trickedout -- ���ݻ�ͳһ��ɻ������ݻ�\n");
	printf("daisies ----- ����ʬ��ɱ�����һЩ���գ���Ҫ�ǻ����ﵽ100�ף�\n");
	printf("dance ------- �ý�ʬ�ڶ��������裨���δ�� ���δ�Σ�����Ҫ�ǻ����ﵽ500�ף�\n");
	printf("sukhbir ----- �л���ʬ��������ʱ�Ľ�����(>��<*) \n");
	printf("pinata ------ ��ʬ����ɢ��һ�ص��ǹ�����Ҫ�ǻ����ﵽ1000�ף�\n");
	pause();
}

//ʱ���߳� 
void TimerThread(){
	TimerIsExit=FALSE;
	TimerIsRun=TRUE;
	
	int vaseNum;
	ReadProcessMemory(hProcess,(LPCVOID)getMemory_2(hProcess,0x006A9EC0,0x768,0x12C,4),&vaseNum,4,NULL);
	if(vaseNum==0){
		TimerIsRun=FALSE;
		TimerIsExit=TRUE;
		goto exit;
	} 
	while(!TimerIsExit){
		if (TimerIsRun){
			int vase_i;
			for(vase_i=0;vase_i<vaseNum;vase_i++){
				if(writeMod_3(hProcess,0x006A9EC0,0x768,0x11C,vase_i*0xEC+0x4C,100,4)==0){
					TimerIsRun=FALSE;
					TimerIsExit=TRUE;
					break;
				}
			}
			Sleep(TimerDelay);
		}
	}
	exit:
		ExitThread(EXIT_SUCCESS);
}

//����������ɫ
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); 
}
