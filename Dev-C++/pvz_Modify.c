/*ֲ���ս��ʬC�����޸���*/

//�Ƿ�Ϊ���԰汾
#define DEBUG 0

#include <stdio.h>
#include <conio.h>
#include "mod.h"

//��Ϸ��������
char processName[]="PlantsVsZombies.exe";
//����
int command;
//�������PID
DWORD Pid;
//����ȫ�ֽ��̾��
HANDLE hProcess=0;

//�����Ƿ��Ѿ�����
BOOL isRun=FALSE;
//�Ƿ��̨���б�ʶ
BOOL backStage=TRUE;
//�Ƿ��ص����ñ�ʶ
BOOL anyPosition=FALSE;
//�Ƿ���С��ʬ��Ч��ʶ
BOOL isLittle=FALSE;

/*��������*/
BOOL openGameProcess();
BOOL openModify();
void menu();
void upData();
void Choice();
void cheatMsg(BOOL isSuccess,const char msg[]);
void noOperation();
void pause();
void showMiniGameList();
void cheatCode();
void showOpenCheat();
int limit(int value,int min,int max);
void color(int c);

/*������*/
int main(void){
	//���ó������
	SetConsoleTitle("��ֲ���ս��ʬ�� C�����޸��� v0.21");
	//�����Ϸ����
	isRun=openGameProcess();
	
	while(1){
		menu();
		color(14);
		
		printf("\n�밴�°���ѡ��ѡ�");
		command=getchar();
		Choice();
	}
	
	return 0;
}

//�򿪽���
BOOL openGameProcess(){
	color(14);
	printf("���ڴ򿪽���...\n");
	
	//Ѱ�ҽ������Ʋ�����pid
	if(FindProcessPid(processName,Pid)){
		printf("[%s][Pid��%d]\n",processName,Pid);
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if (hProcess!=0){
			color(10);
			printf("\n�ɹ�����Ϸ����[%s]�����̾����%d\n",processName,hProcess);
			//���汾�Ƿ�ΪӢ��ԭ��ͺ���һ������
			if(readMemory(hProcess,0x42748E,0,4)==0xFF563DE8){
				return TRUE;
			}else{
				color(14);
				printf("\n��֧�ֵ���Ϸ�汾��Ŀǰ��֧��Ӣ��ԭ��ͺ���һ��/����\n");
				return FALSE;
			}
		}else{
			color(12);
			printf("\n����Ϸ����[%s]ʧ��\n",processName);
		}
	}else{
		color(14);
		printf("δ�ҵ���Ϸ���̣�%s\n",processName);
	}
	
	return FALSE;
}

//�޸����Ƿ��Ѿ�������Ϸ����
BOOL openModify(){
	if(hProcess==0){
		color(14);
		printf("\n���ȴ��޸���������Ϸ�����\n");
		return FALSE;
	}
	
	return TRUE;
}

//���˵�
void menu(){
	color(15);
	printf("\n����������������������������������������\n");
	printf("��ֲ���ս��ʬ�� C�����޸���\n\n");
	printf("O�����´�/��������[%s]\n",processName);
	if(isRun){
		#if DEBUG
			printf("T�����Դ��루Debug��\n");
		#endif
		printf("\na�������޸ģ�\n");
		printf("1���޸�����\n");
		printf("2���޸Ľ�Ǯ\n");
		printf("3������ȫ������ȴʱ��\n");
		printf("4�������̨���У��ٿ�һ��ȡ����\n");
		printf("5���޸Ŀ��۸���\n");
		printf("6���Զ��ռ���Դ\n");

		printf("\nb���ؿ��޸ģ�\n");
		printf("1��ð��ģʽ����\n");
		printf("2��С��Ϸ���أ����ҹؿ���\n");

		printf("\nc��ֲ���޸ģ�\n");
		printf("1�������ص����ã��ٿ�һ��ȡ����\n");
		printf("2���Ͽ���ֲ������\n");

		printf("\nd����ʬ�޸ģ�\n");
		printf("1����ɱ�������н�ʬ\n");
		printf("2��С��ʬ��Ч���ٿ�һ�λָ�������С��\n");

		printf("\ne����԰�޸ģ�\n");
		printf("1���޸��ǻ����߶�\n");
		printf("2���ɿ��������޸�\n");

		printf("\nf�������޸ģ�\n");
		printf("1����ƿ͸��\n");
		printf("2����ʾ����С��Ϸ\n");
	}
	printf("\n���⹦�ܣ�\n");
	printf("~���鿴�޸������¹���\n");
	printf("!���鿴����С��Ϸ������ģʽ������ģʽ�ؿ�����\n");
	printf("@���鿴PVZ�����루�ʵ�����ȫ\n");
	printf("#���鿴Ŀǰ�Ѿ�������Ч��\n");
	printf("A�����ڱ��޸�����Ϣ\n");
	printf("\nE���˳��޸���");
	printf("\n����������������������������������������\n");
}

//���¹���
void upData(){
	color(9);
	printf("\n���¹���\n\n");
	printf("v0.1 [2019.3.4] �����������ʮ�����ܣ�1~0��\n");
	printf("v0.2 [2019.3.13] �������¹��ܣ�\n");
	printf("\t(1)�Զ��ռ���Դ\n\t(2)��ʾ����С��Ϸ\n\t(3)�ص�����\n\t(4)�ɿ����޸�\n\t(5)С��ʬ��Ч\n\t(6)�Ͽ���ֲ������\n");
	printf("�޸�/��ǿ�����¹��ܣ�\n");
	printf("\t(1)��ƿ͸�Ӳ��ȶ����޸�\n\t(2)��ɱ��ʬ���ȶ����޸�\n");
	printf("v0.21 [2019.7.28] �Ż��ڴ��д����\n");
	
	pause();
}

//�ж�ѡ��
void Choice(){
	//�м�ֵ
	int _tempValue;
	
	color(13);
	//�����ַ��ж�Ӧ��ִ��ʲô����
	switch(command){
		case 'O':
			isRun=openGameProcess();
			pause();
			break;
		#if DEBUG
			case 'T':
				if(!openModify()){
					printf("\n��ǰֵΪ��");
				}
				break;
		#endif
		//�����޸�
		case 'a':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify()){
						printf("\n������Ҫ�޸ĵ�����������");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,0,9990);
						cheatMsg(writeMemory(hProcess,0x006A9EC0,2,_tempValue,4,0x768,0x5560),"����");
					}
					break;
				case '2':
					if(openModify()){
						printf("\n������Ҫ�޸ĵĽ�Ǯ������");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,0,99999);
						cheatMsg(writeMemory(hProcess,0x006A9EC0,2,_tempValue,4,0x82C,0x28),"��Ǯ");
					}
					break;
				case '3':
					if(openModify())cheatMsg(writeMemory(hProcess,0x00487296,0,0x1477,2),"��������ȴ");
					break;
				case '4':
					if(openModify()){
						if(backStage){
							cheatMsg(writeMemory(hProcess,0x0054EBEF,0,0xC3,1),"ȡ����̨");
						}else{
							cheatMsg(writeMemory(hProcess,0x0054EBEF,0,0x57,1),"�ָ���̨");
						}
						backStage=!backStage;
					}
					break;
				case '5':
					if(openModify()){
						printf("\n������Ҫ�޸ĵĿ��۸�����1~10����");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,1,10);
						cheatMsg(writeMemory(hProcess,0x006A9EC0,3,_tempValue,4,0x768,0x144,0x24),"���۸���");
					}
					break;
				case '6':
					if(openModify())cheatMsg(writeMemory(hProcess,0x0043158F,0,0xEB,1),"�Զ��ռ�����");
					break;
				default :
					noOperation();
			}
			break;
		//�ؿ��޸�
		case 'b':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾�ؿ��޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify()){
						printf("\n������Ҫ�޸ĵ�ð�չؿ���������Ҫȥ4-3�ؿ�����ôӦ������43����");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,11,99);
						_tempValue-=10;
						cheatMsg(writeMemory(hProcess,0x006A9EC0,2,_tempValue,4,0x82C,0x24),"ð��ģʽ�ؿ�");
					}
					break;
				case '2':
					if(openModify()){
						printf("\n��Ҫ�Ƚ�������ؿ�Ȼ�����˵���һ��Ҫ��ô�����������������޸���Ч���������¿�ʼ�������ģʽ�µĴ浵����ע�ⱸ�ݴ浵�����޸Ĺؿ�����Ȼ�������¿�ʼ����������¿�ʼ�Ļ�����������ҹؿ���Ч��\n");
						printf("������Ҫ�����������ϷID��ID��ͨ����ѯ��!���˵��Ĺؿ����루1~70������");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,1,70);
						cheatMsg(writeMemory(hProcess,0x006A9EC0,1,_tempValue,4,0x7F8),"С��Ϸ����");
					}
					break;
				default :
					noOperation();
			}
			break;
		//ֲ���޸�
		case 'c':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾ֲ���޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify()){
						if(!anyPosition){
							cheatMsg(writeMemory(hProcess,0x0040FE30,0,0x81,1)&&writeMemory(hProcess,0x00438E40,0,0xEB,1)&&writeMemory(hProcess,0x0042A2D9,0,0x8D,1),"�����ص�����");
						}else{
							cheatMsg(writeMemory(hProcess,0x0040FE30,0,0x84,1)&&writeMemory(hProcess,0x00438E40,0,0x74,1)&&writeMemory(hProcess,0x0042A2D9,0,0x84,1),"ȡ���ص�����");
						}
						anyPosition=!anyPosition;
					}
					break;
				case '2':
					if(openModify())cheatMsg(writeMemory(hProcess,0x0041D7D0,0,0xC301B0,3)&&writeMemory(hProcess,0x0040E477,0,0xEB,1),"�Ͽ���ֲ������");
					break;
				default :
					noOperation();
			}
			break;
		//��ʬ�޸�
		case 'd':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾��ʬ�޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify()){
						int z_i;
						BOOL kill=FALSE;
						DWORD z_status;
						//pvz�������Ľ�ʬ������1024��������ѭ��1024�ξͿ�����ɱ���н�ʬ��
						for(z_i=0;z_i<1024;z_i++){
							z_status=readMemory(hProcess,0x006A9EC0,3,4,0x768,0x90,z_i*0x15C+0xEC);
							//printf("��ʬ״̬��%d",z_status);
							if(z_status==0)kill=writeMemory(hProcess,0x006A9EC0,3,3,4,0x768,0x90,z_i*0x15C+0x28);
						}
						cheatMsg(kill,"��ɱȫ����ʬ");
					}
					break;
				case '2':
					if(openModify()){
						if(!isLittle){
							cheatMsg(writeMemory(hProcess,0x00523ED5,0,0xEB,1),"����С��ʬ��Ч");
						}else{
							cheatMsg(writeMemory(hProcess,0x00523ED5,0,0x74,1),"�ر�С��ʬ��Ч");
						}
						isLittle=!isLittle;
					}
					break;
				default :
					noOperation();
			}
			break;
		//��԰�޸�
		case 'e':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾��԰�޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify()){
						printf("\n������Ҫ�޸ĵ��ǻ����߶ȣ�");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,0,2147483647);
						cheatMsg(writeMemory(hProcess,0x006A9EC0,2,_tempValue,4,0x82C,0xF4),"�ǻ����߶�");
					}
					break;
				case '2':
					if(openModify()){
						printf("\n������Ҫ�޸ĵ��ɿ���������");
						scanf("%d",&_tempValue);
						_tempValue=limit(_tempValue,0,999);
						_tempValue+=1000;
						cheatMsg(writeMemory(hProcess,0x006A9EC0,2,_tempValue,4,0x82C,0x228),"�ɿ�������");
					}
					break;
				default :
					noOperation();
			}
			break;
		//�����޸�
		case 'f':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			color(14);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			color(13);
			switch(command){
				case '1':
					if(openModify())cheatMsg(writeMemory(hProcess,0x0044E5CC,0,0x0033B866,4),"��ƿ͸�ӿ���");
					break;
				case '2':
					if(openModify())cheatMsg(writeMemory(hProcess,0x0042DF5D,0,0x38,1),"��ʾ����С��Ϸ");
					break;
				default :
					noOperation();
			}
			break;
		//~
		case '\x7E':
			upData();
			break;
		//!
		case '\x21':
			showMiniGameList();
			break;
		//@
		case '\x40':
			cheatCode();
			break;
		//#
		case '\x23':
			showOpenCheat();
			break;
		case 'A':
			printf("\n���ڣ���������ֲ���ս��ʬ��PlantsVsZombies�����޸�����ʹ�á�Dev-C++����������\n�޸������ߣ���ˮ������\n��л��ҵ�ʹ�ã����κ����ʺ�bug���Է�������\n\n");
			pause();
			break;
		case 'E':
			exit(0);
			break;
		default :
			noOperation();
	}
	
	//�ݻ�����
	getchar();
}

//�޸���Ϣ
void cheatMsg(BOOL isSuccess,const char msg[]){
	if(isSuccess){
		color(10);
		printf("\n�޸ġ�%s���ɹ���\n",msg);
	}else{
		color(12);
		printf("\n�޸ġ�%s��ʧ�ܣ�\n",msg);
	}
	
	pause();
}

//�Ҳ�������
void noOperation(){
	color(14);
	printf("\n�Ҳ�����ز������������������������\n");
	
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
	
	printf("\nС��Ϸ���루��ɫ�ӡ�*����־�Ĺؿ���������/���ң�����ɱ����˳���\n\n");
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
	
	int gameLength=sizeof(MiniGame)/sizeof(MiniGame[0]);
	int i;
	for(i=0;i<gameLength;i++){
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

//��ʾ�������޸���Ŀ
void showOpenCheat(){
	color(11);
	printf("\n��ǰ�������޸���Ŀ\n\n");
	
	color(13);
	BOOL sign=FALSE;
	if(!backStage){
		printf("ȡ����̨����������\n");
		sign=TRUE;
	}
	if(anyPosition){
		printf("�ص����ù���������\n");
		sign=TRUE;
	}
	if(isLittle){
		printf("С��ʬ��Ч������\n");
		sign=TRUE;
	}
	
	if(!sign)printf("Ŀǰû���޸���Ŀ��������\n");
	
	pause();
}

//�������ݴ�С
int limit(int value,int min,int max){
	if(value<min)return min;
	if(value>max)return max;
	
	return value;
} 

//����������ɫ
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
