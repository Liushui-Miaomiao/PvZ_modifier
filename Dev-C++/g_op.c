/*Game Operation*/

#include "headgr.h"

extern char processName[];
extern DWORD Pid;
extern HANDLE hProcess;
extern int command;

extern BOOL isRun;
extern BOOL backStage;
extern BOOL anyPosition;
extern BOOL isLittle; 

/*����Ϸ����*/
BOOL openGameProcess(void){
	setColor(14);
	printf("���ڴ򿪽���...\n");
	
	//Ѱ�ҽ������Ʋ�����pid
	if(FindProcessPid(processName,Pid)){
		printf("[%s][Pid��%d]\n",processName,Pid);
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		
		if (hProcess!=0){
			setColor(10);
			printf("\n�ɹ�����Ϸ����[%s]�����̾����%d\n",processName,hProcess);
			
			if(readMemory(hProcess,0x42748E,0,4)==0xFF563DE8){
				return TRUE;
			}else{
				setColor(14);
				printf("\n��֧�ֵ���Ϸ�汾��Ŀǰ��֧��Ӣ��ԭ��ͺ���һ��/����\n");
				return FALSE;
			}
		}else{
			setColor(12);
			printf("\n����Ϸ����[%s]ʧ��\n",processName);
		}
	}else{
		setColor(14);
		printf("δ�ҵ���Ϸ���̣�%s\n",processName);
	}
	
	return FALSE;
}

/*�Ƿ��Ѿ���ȡ��Ϸ����*/
BOOL openModify(void){
	if(hProcess==0){
		setColor(14);
		printf("\n���ȴ��޸���������Ϸ�����\n");
		return FALSE;
	}
	
	return TRUE;
}

/*ѡ������*/
void Choice(void){
	//������
	int _tempValue;
	
	setColor(13);
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
		
		/*�����޸�*/
		case 'a':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
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
		
		/*�ؿ��޸�*/
		case 'b':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾�ؿ��޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
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
		
		/*ֲ���޸�*/
		case 'c':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾ֲ���޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
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
		
		/*��ʬ�޸�*/
		case 'd':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾��ʬ�޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
			switch(command){
				case '1':
					if(openModify()){
						int z_i;
						BOOL kill=FALSE;
						DWORD z_status;
						/*pvz�����1024ֻ��ʬ*/
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
		
		/*��԰�޸�*/
		case 'e':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾��԰�޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
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
		
		/*�����޸�*/
		case 'f':
			if(!openModify()){
				pause();
				break;
			}
			
			getchar();
			setColor(14);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			command=getchar();
			setColor(13);
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
			about();
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

/*�淶���ݷ�Χ*/
int limit(int value,int min,int max){
	if(value<min)return min;
	if(value>max)return max;
	
	return value;
}
