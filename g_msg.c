/*Game Message*/

#include "header\g_msg.h"
#include "header\public\color.h"

extern BOOL g_bIsRun;
extern BOOL g_bIsBackStageRun;
extern BOOL g_bIsAnyPosition;
extern BOOL g_bIsLittleZombie;

/*g_op - Game Operation*/
void pause(void);

/*���˵�*/
void menu(void){
	setColor(BRIGHT_WHITE);
	puts("\n����������������������������������������������������");
	puts("��ֲ���ս��ʬ�� C�����޸���\n");
	puts("O�����´�/��������\n");
	if(g_bIsRun){
		#if DEBUG
			puts("T�����Դ��루Debug��\n");
		#endif
		setColor(BRIGHT_CYAN);
		puts("a�������޸ģ�\t\t  b���ؿ��޸ģ�");
		setColor(BRIGHT_WHITE);
		puts("1���޸�����\t\t  1��ð��ģʽ����");
		puts("2���޸Ľ�Ǯ\t\t  2��С��Ϸ���أ����ҹؿ���");
		puts("3����������ȴʱ��");
		puts(g_bIsBackStageRun?"4��ȡ����̨����":"4�������̨����");
		puts("5���޸Ŀ��۸���");
		puts("6���Զ��ռ���Դ\n");
		
		setColor(BRIGHT_CYAN);
		puts("c��ֲ���޸ģ�\t\t  d����ʬ�޸ģ�");
		setColor(BRIGHT_WHITE);
		printf("%s\t\t  1����ɱ�������н�ʬ\n",g_bIsAnyPosition?"1��ȡ���ص�����":"1�������ص�����");
		printf("2���Ͽ���ֲ������\t  %s\n",g_bIsLittleZombie?"2���ر�С��ʬ��Ч\n":"2������С��ʬ��Ч\n");
		
		setColor(BRIGHT_CYAN);
		puts("e����԰�޸ģ�\t\t  f�������޸ģ�");
		setColor(BRIGHT_WHITE);
		puts("1���޸��ǻ����߶�\t  1����ƿ͸��");
		puts("2���ɿ��������޸�\t  2����ʾ����С��Ϸ\n");
	}
	setColor(BRIGHT_CYAN);
	puts("���⹦�ܣ�");
	setColor(BRIGHT_WHITE);
	puts("~���鿴�޸������¹���\t  !���鿴�ؿ�����");
	puts("@���鿴PVZС�����ȫ\t  #���鿴�Ѿ�������Ч��");
	puts("A�����ڱ��޸�����Ϣ\t  E���˳��޸���\n");
	puts("����������������������������������������������������");
}

/*������Ϣ*/
void upDate(void){
	setColor(BRIGHT_BLUE);
	puts("\n���¹���\n");
	puts("v0.1 [2019.03.04] �����������ʮ�����ܣ�1~0��");
	
	puts("v0.2 [2019.03.13] �������¹��ܣ�");
	puts("\t(1)�Զ��ռ���Դ\n\t(2)��ʾ����С��Ϸ\n\t(3)�ص�����\n\t(4)�ɿ����޸�\n\t(5)С��ʬ��Ч\n\t(6)�Ͽ���ֲ������");
	puts("�޸�/��ǿ�����¹��ܣ�");
	puts("\t(1)��ƿ͸�Ӳ��ȶ����޸�\n\t(2)��ɱ��ʬ���ȶ����޸�");
	puts("v0.21 [2019.07.28] �Ż��ڴ��д����");
	puts("v0.22 [2019.09.16] �Ż��ļ��ṹ");
	
	pause();
}

/*С����*/
void cheatCode(void){
	setColor(MAGENTA);
	puts("\nPVZС�����ȫ�������ǻ�����һ���߶��ǻ����������ģ�\n");
	puts("future ------ ��ʬ����ʱ��̫���۾�");
	puts("mustache ---- ��ʬ������Ʋ����");
	puts("trickedout -- ���ݻ�ͳһ��ɻ������ݻ�");
	puts("daisies ----- ����ʬ��ɱ�����һЩ���գ���Ҫ�ǻ����ﵽ100�ף�");
	puts("dance ------- �ý�ʬ�ڶ��������裨���δ�� ���δ�Σ�����Ҫ�ǻ����ﵽ500�ף�");
	puts("sukhbir ----- �л���ʬ��������ʱ�Ľ�����(>��<*)");
	puts("pinata ------ ��ʬ����ɢ��һ�ص��ǹ�����Ҫ�ǻ����ﵽ1000�ף�");
	
	pause();
}

/*��ʾ������Ϸ�б�*/
void showMiniGameList(void){
	setColor(BRIGHT_CYAN);
	
	puts("\nС��Ϸ���루��ɫ�ӡ�*����־�Ĺؿ���������/���ң�����ɱ����˳���\n");
	const char *miniGameList[]={"����ģʽ������","����ģʽ����ҹ","����ģʽ��Ӿ��","����ģʽ��Ũ��","����ģʽ���ݶ�",
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
	
	int i;
	int iGameListLength=sizeof(miniGameList)/sizeof(miniGameList[0]);
	for(i=0;i<iGameListLength;i++){
		if(i==37||i==42||i==49){
			setColor(BRIGHT_RED);
			putchar('*');
		}else{
			setColor(BRIGHT_CYAN);
		}
		printf("%d.%s\n",i+1,miniGameList[i]);
	}
	
	pause();
}

/*�Ҳ�������*/
void noOperation(void){
	setColor(BRIGHT_YELLOW);
	puts("\n�Ҳ�����ز������������������������");
	
	pause();
}

/*������Ϣ*/
void about(void){
	puts("\n���ڣ���������ֲ���ս��ʬ��Plants vs. Zombies�����޸�����ʹ�á�Dev-C++����������");
	puts("�޸������ߣ���ˮ������\n��л��ҵ�ʹ�ã����κ����ʺ�bug���Է�������");
	
	pause();
}

/*��ʾ�޸���ʾ��Ϣ*/
void cheatMsg(BOOL bIsSuccess,const char cMsg[]){
	if(bIsSuccess){
		setColor(BRIGHT_GREEN);
		printf("\n�޸ġ�%s���ɹ���\n",cMsg);
	}else{
		setColor(BRIGHT_RED);
		printf("\n�޸ġ�%s��ʧ�ܣ�\n",cMsg);
	}
	
	pause();
}

/*��ʾ�������޸���Ŀ*/
void showOpenCheat(void){
	setColor(BRIGHT_CYAN);
	puts("\n��ǰ�������޸���Ŀ\n");
	
	setColor(BRIGHT_MAGENTA);
	
	BOOL bSign=FALSE;
	if(g_bIsBackStageRun){
		puts("ȡ����̨����������");
		bSign=TRUE;
	}
	if(g_bIsAnyPosition){
		puts("�ص����ù���������");
		bSign=TRUE;
	}
	if(g_bIsLittleZombie){
		puts("С��ʬ��Ч������");
		bSign=TRUE;
	}
	
	if(!bSign){
		puts("Ŀǰû���޸���Ŀ��������");
	}
	
	pause();
}

/*��ʾ��������*/
void showProcessName(const char cMsgFirst[],const char cMsgLast[]){
	printf("%s%s%s",cMsgFirst,PROCESS_NAME,cMsgLast);
}
