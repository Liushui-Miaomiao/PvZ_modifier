/*Game Operation*/

#include "headgr.h"

extern DWORD g_dwPid;
extern HANDLE g_hProcess;
extern int g_iCommand;

extern BOOL g_bIsRun;
extern BOOL g_bIsBackStageRun;
extern BOOL g_bIsAnyPosition;
extern BOOL g_bIsLittleZombie; 

/*��ʼ���޸���*/
void initModifier(void){
	SetConsoleTitle("��ֲ���ս��ʬ�� C�����޸��� v0.22");
	g_bIsRun=openGameProcess();
}

/*����Ϸ����*/
BOOL openGameProcess(void){
	setColor(BRIGHT_YELLOW);
	printf("���ڴ򿪽���...\n");
	
	//Ѱ�ҽ������Ʋ�����pid
	if(findProcessPidByName(PROCESS_NAME,g_dwPid)){
		showProcessName("[","]");
		printf("[Pid��%d]\n",g_dwPid);
		
		g_hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,g_dwPid);
		
		if (g_hProcess!=0){
			setColor(BRIGHT_GREEN);
			showProcessName("\n�ɹ�����Ϸ����[","]��");
			printf("���̾����%d\n",g_hProcess);
			
			if(readMemory(g_hProcess,0x42748E,0,4)==0xFF563DE8){
				if(readMemory(g_hProcess,0x0054EBEF,0,1)==0xFF563DC3){
					g_bIsBackStageRun=TRUE;
				}
				if(readMemory(g_hProcess,0x0040FE30,0,1)==0xFF563D81&&readMemory(g_hProcess,0x00438E40,0,1)==0xFF563DEB&&readMemory(g_hProcess,0x0042A2D9,0,1)==0xFF563D8D){
					g_bIsAnyPosition=TRUE;
				}
				if(readMemory(g_hProcess,0x00523ED5,0,1)==0xFF563DEB){
					g_bIsLittleZombie=TRUE;
				}
				
				return TRUE;
			}else{
				setColor(BRIGHT_YELLOW);
				printf("\n��֧�ֵ���Ϸ�汾��\n");
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
	if(g_hProcess==0){
		setColor(BRIGHT_YELLOW);
		printf("\n���ȴ��޸���������Ϸ�����\n");
		return FALSE;
	}
	
	return TRUE;
}

/*ѡ������*/
void choice(void){
	//������
	int l_iTempValue;
	
	setColor(BRIGHT_MAGENTA);
	//�����ַ��ж�Ӧ��ִ��ʲô����
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
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵ�����������");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,9990);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x768,0x5560),"����");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵĽ�Ǯ������");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,99999);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x28),"��Ǯ");
					}
					break;
				case '3':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x00487296,0,0x1477,2),"��������ȴ");
					break;
				case '4':
					if(openModifier()){
						if(!g_bIsBackStageRun){
							cheatMsg(writeMemory(g_hProcess,0x0054EBEF,0,0xC3,1),"ȡ����̨");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x0054EBEF,0,0x57,1),"�ָ���̨");
						}
						g_bIsBackStageRun=!g_bIsBackStageRun;
					}
					break;
				case '5':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵĿ��۸�����1~10����");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,1,10);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,3,l_iTempValue,4,0x768,0x144,0x24),"���۸���");
					}
					break;
				case '6':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0043158F,0,0xEB,1),"�Զ��ռ�����");
					break;
				default :
					noOperation();
			}
			break;
		
		/*�ؿ��޸�*/
		case 'b':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾�ؿ��޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵ�ð�չؿ���������Ҫȥ4-3�ؿ�����ôӦ������43����");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,11,99)-10;
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x24),"ð��ģʽ�ؿ�");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n��Ҫ�Ƚ�������ؿ�Ȼ�����˵���һ��Ҫ��ô�����������������޸���Ч���������¿�ʼ�������ģʽ�µĴ浵����ע�ⱸ�ݴ浵����");
						printf("�޸Ĺؿ�����Ȼ�������¿�ʼ����������¿�ʼ�Ļ�����������ҹؿ���Ч��\n");
						printf("������Ҫ�����������ϷID��ID��ͨ����ѯ��!���˵��Ĺؿ����루1~70������");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,1,70);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,1,l_iTempValue,4,0x7F8),"С��Ϸ����");
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*ֲ���޸�*/
		case 'c':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾ֲ���޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						if(!g_bIsAnyPosition){
							cheatMsg(writeMemory(g_hProcess,0x0040FE30,0,0x81,1)&&writeMemory(g_hProcess,0x00438E40,0,0xEB,1)&&writeMemory(g_hProcess,0x0042A2D9,0,0x8D,1),"�����ص�����");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x0040FE30,0,0x84,1)&&writeMemory(g_hProcess,0x00438E40,0,0x74,1)&&writeMemory(g_hProcess,0x0042A2D9,0,0x84,1),"ȡ���ص�����");
						}
						g_bIsAnyPosition=!g_bIsAnyPosition;
					}
					break;
				case '2':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0041D7D0,0,0xC301B0,3)&&writeMemory(g_hProcess,0x0040E477,0,0xEB,1),"�Ͽ���ֲ������");
					break;
				default :
					noOperation();
			}
			break;
		
		/*��ʬ�޸�*/
		case 'd':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾��ʬ�޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						int i;
						BOOL bKill=FALSE;
						printf("��ʬ������%d\n",readMemory(g_hProcess,0x006A9EC0,2,4,0x768,0xA0));
						/*pvz�����1024ֻ��ʬ*/
						for(i=0;i<1024;i++){
							if(readMemory(g_hProcess,0x006A9EC0,3,4,0x768,0x90,i*0x15C+0xEC)==0){
								bKill=writeMemory(g_hProcess,0x006A9EC0,3,3,4,0x768,0x90,i*0x15C+0x28);
							}
						}
						cheatMsg(bKill,"��ɱȫ����ʬ");
					}
					break;
				case '2':
					if(openModifier()){
						if(!g_bIsLittleZombie){
							cheatMsg(writeMemory(g_hProcess,0x00523ED5,0,0xEB,1),"����С��ʬ��Ч");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x00523ED5,0,0x74,1),"�ر�С��ʬ��Ч");
						}
						g_bIsLittleZombie=!g_bIsLittleZombie;
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*��԰�޸�*/
		case 'e':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾��԰�޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵ��ǻ����߶ȣ�");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,2147483647);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0xF4),"�ǻ����߶�");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n������Ҫ�޸ĵ��ɿ���������");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,999)+1000;
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x228),"�ɿ�������");
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*�����޸�*/
		case 'f':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n�ѽ��롾�����޸ġ��˵�����ѡ����ѡ�");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0044E5CC,0,0x0033B866,4),"��ƿ͸�ӿ���");
					break;
				case '2':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0042DF5D,0,0x38,1),"��ʾ����С��Ϸ");
					break;
				default :
					noOperation();
			}
			break;
		//~
		case '\x7E':
			upDate();
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
			close();
			break;
		default :
			noOperation();
	}
	
	//�ݻ�����
	getchar();
}

/*�淶���ݷ�Χ*/
int limit(int iValue,int iMin,int iMax){
	if(iValue<iMin)return iMin;
	if(iValue>iMax)return iMax;
	
	return iValue;
}
