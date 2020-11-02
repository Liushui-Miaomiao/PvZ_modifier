#include "public_header.h"

#include "message.h"
#include "color.h"
#include "process.h"
#include "modifiy.h"

#include <conio.h>

extern BOOL g_bGameIsRun;
extern BOOL g_bIsBackStageRun;
extern BOOL g_bIsAnyPosition;
extern BOOL g_bIsLittleZombie;
extern DWORD* p_dwBuffer;

static void OperationNotFound(void);
static void BranchUniversal(void);
static void BranchCheckpoint(void);
static void BranchPlants(void);
static void BranchZombies(void);
static void BranchGarden(void);
static void BranchOther(void);
static void Updata(void);
static void CheatCode(void);
static void ShowGameList(void);
static void About(void);
static void ExecutionInformation(BOOL bIsSuccess, char* cMessage);
static void StartedProject(void);

void Menu(void) {
	SetColor(BRIGHT_WHITE);
	puts("\n����������������������������������������������������");
	puts("��ֲ���ս��ʬ�� C�����޸���\n");
	puts("O�����´�/��������\n");
	if (g_bGameIsRun) {
		SetColor(BRIGHT_CYAN);
		puts("a�������޸ģ�\t\t\tb���ؿ��޸ģ�");
		SetColor(BRIGHT_WHITE);
		puts("1���޸�����\t\t\t1��ð��ģʽ����");
		puts("2���޸Ľ�Ǯ\t\t\t2��С��Ϸ���أ����ҹؿ���");
		puts("3����������ȴʱ��");
		puts(g_bIsBackStageRun ? "4��ȡ����̨����" : "4�������̨����");
		puts("5���޸Ŀ��۸���");
		puts("6���Զ��ռ���Դ\n");

		SetColor(BRIGHT_CYAN);
		puts("c��ֲ���޸ģ�\t\t\td����ʬ�޸ģ�");
		SetColor(BRIGHT_WHITE);
		printf("%s\t\t\t1����ɱ�������н�ʬ\n", g_bIsAnyPosition ? "1��ȡ���ص�����" : "1�������ص�����");
		printf("2���Ͽ���ֲ������\t\t%s\n", g_bIsLittleZombie ? "2���ر�С��ʬ��Ч\n" : "2������С��ʬ��Ч\n");

		SetColor(BRIGHT_CYAN);
		puts("e����԰�޸ģ�\t\t\tf�������޸ģ�");
		SetColor(BRIGHT_WHITE);
		puts("1���޸��ǻ����߶�\t\t1����ƿ͸��");
		puts("2���ɿ��������޸�\t\t2����ʾ����С��Ϸ\n");
	}
	SetColor(BRIGHT_CYAN);
	puts("���⹦�ܣ�");
	SetColor(BRIGHT_WHITE);
	puts("~���鿴�޸������¹���\t\t!���鿴�ؿ�����");
	puts("@���鿴PVZС�����ȫ\t\t#���鿴�Ѿ�������Ч��");
	puts("A�����ڱ��޸�����Ϣ\t\tE���˳��޸���\n");
	puts("����������������������������������������������������");
}

void Select(void) {
	SetColor(BRIGHT_YELLOW);
	printf("��ѡ��Ҫ���еĲ�����");
	char l_iCommand = 0;
	scanf_s("%c", &l_iCommand, 1);
	//printf("%d", l_iCommand);

	SetColor(BRIGHT_MAGENTA);
	switch (l_iCommand) {
	case 'O':
		g_bGameIsRun = OpenGameProcess();
		break;
	case 'a':																//����ѡ���֧�ж�
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		if (!g_bGameIsRun) {												//�������δ����״̬
			SetColor(BRIGHT_YELLOW);
			puts("\n���ȴ��޸���������Ϸ�����");

			Pause();
			break;
		}

		getchar();
		SetColor(BRIGHT_YELLOW);

		switch (l_iCommand) {
		case 'a':
			BranchUniversal();
			break;
		case 'b':
			BranchCheckpoint();
			break;
		case 'c':
			BranchPlants();
			break;
		case 'd':
			BranchZombies();
			break;
		case 'e':
			BranchGarden();
			break;
		case 'f':
			BranchOther();
			break;
		}
		break;
	case '~':
		Updata();
		break;
	case '!':
		ShowGameList();
		break;
	case '@':
		CheatCode();
		break;
	case '#':
		StartedProject();
		break;
	case 'A':
		About();
		break;
	case 'E':
		Close();
		break;
	default :
		OperationNotFound();
	}
}

static void OperationNotFound(void) {
	SetColor(BRIGHT_YELLOW);
	puts("\n�Ҳ�����ز�����");

	Pause();
}

static void BranchUniversal(void) {
	printf("\n�ѽ���[�����޸�]�˵�����ѡ��Ҫ���еĲ�����");
	int l_iCommand = getchar();
	SetColor(BRIGHT_MAGENTA);

	switch (l_iCommand) {
	case '1':
		printf("\n������Ҫ�޸ĵ�����������");
		scanf_s("%d",p_dwBuffer);
		ExecutionInformation(ChangeSunLight(),"����");
		break;
	case '2':
		printf("\n������Ҫ�޸ĵĽ�Ǯ������");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeMoney(), "��Ǯ");
		break;
	case '3':
		ExecutionInformation(CardNoCD(), "��������ȴ");
		break;
	case '4':
		ExecutionInformation(AllowBackStageRun(!g_bIsBackStageRun), g_bIsBackStageRun ? "�ָ���̨" : "ȡ����̨");
		g_bIsBackStageRun = !g_bIsBackStageRun;
		break;
	case '5':
		printf("\n������Ҫ�޸ĵĿ��۸�����");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeCardNum(), "���۸���");
		break;
	case '6':
		ExecutionInformation(AutoCollect(), "�Զ��ռ�����");
		break;
	default:
		OperationNotFound();
	}
}

static void BranchCheckpoint(void) {
	printf("\n�ѽ���[�ؿ��޸�]�˵�����ѡ��Ҫ���еĲ�����");
	int l_iCommand = getchar();
	SetColor(BRIGHT_MAGENTA);

	switch (l_iCommand) {
	case '1':
		printf("\n������Ҫ�޸ĵ�ð�չؿ���");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(AdventureJumpLevel(), "ð�չؿ�");
		break;
	case '2':
		printf("\n������Ҫ�����������ϷID��");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeMoney(), "��Ǯ");
		break;
	default:
		OperationNotFound();
	}
}

static void BranchPlants(void) {

}

static void BranchZombies(void) {

}

static void BranchGarden(void) {

}

static void BranchOther(void) {

}

static void Updata(void) {
	SetColor(BRIGHT_BLUE);
	puts("\n���¹���\n");
	puts("v0.1 [2019.03.04] �����������ʮ�����ܣ�1~0��");

	puts("v0.2 [2019.03.13] �������¹��ܣ�");
	puts("\t(1)�Զ��ռ���Դ\n\t(2)��ʾ����С��Ϸ\n\t(3)�ص�����\n\t(4)�ɿ����޸�\n\t(5)С��ʬ��Ч\n\t(6)�Ͽ���ֲ������");
	puts("�޸�/��ǿ�����¹��ܣ�");
	puts("\t(1)��ƿ͸�Ӳ��ȶ����޸�\n\t(2)��ɱ��ʬ���ȶ����޸�");
	puts("v0.21 [2019.07.28] �Ż��ڴ��д����");
	puts("v0.22 [2019.09.16] �Ż��ļ��ṹ");

	puts("v0.3 [2020.06.25] ��Dev-CPP����תΪMicrosoft Visual Studio���̡�");

	Pause();
}

static void CheatCode(void) {
	SetColor(MAGENTA);
	puts("\nPVZС�����ȫ�������ǻ�����һ���߶��ǻ����������ģ�\n");
	puts("future ------ ��ʬ����ʱ��̫���۾�");
	puts("mustache ---- ��ʬ������Ʋ����");
	puts("trickedout -- ���ݻ�ͳһ��ɻ������ݻ�");
	puts("daisies ----- ����ʬ��ɱ�����һЩ���գ���Ҫ�ǻ����ﵽ100�ף�");
	puts("dance ------- �ý�ʬ�ڶ��������裨���δ�� ���δ�Σ�����Ҫ�ǻ����ﵽ500�ף�");
	puts("sukhbir ----- �л���ʬ��������ʱ�Ľ�����(>��<*)");
	puts("pinata ------ ��ʬ����ɢ��һ�ص��ǹ�����Ҫ�ǻ����ﵽ1000�ף�");

	Pause();
}

static void ShowGameList(void) {
	SetColor(BRIGHT_CYAN);

	puts("\nС��Ϸ���루��ɫ�ӡ�*����־�Ĺؿ���������/���ң�����ɱ����˳���\n");
	const char* miniGameList[] = { "����ģʽ������","����ģʽ����ҹ","����ģʽ��Ӿ��","����ģʽ��Ũ��","����ģʽ���ݶ�",
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
	int l_iGameListLength = sizeof(miniGameList) / sizeof(miniGameList[0]);
	for (i = 0; i < l_iGameListLength; i++) {
		if (i == 37 || i == 42 || i == 49) {
			SetColor(BRIGHT_RED);
			putchar('*');
		}
		else {
			SetColor(BRIGHT_CYAN);
		}
		printf("%d.%s\n", i + 1, miniGameList[i]);
	}

	Pause();
}

static void About(void) {
	puts("\n���ڣ���������ֲ���ս��ʬ��Plants vs. Zombies�����޸���");
	puts("ʹ�á�Microsoft Visual Studio����������");
	puts("Author : Kujo Game Studio");
	puts("��л��ҵ�ʹ�ã����κ����ʺ�bug���Է�������");

	Pause();
}

static void ExecutionInformation(BOOL bIsSuccess, char* cMessage) {
	if (bIsSuccess) {
		SetColor(BRIGHT_GREEN);
		printf("\n�޸�[%s]�ɹ���\n", cMessage);
	}
	else {
		SetColor(BRIGHT_RED);
		printf("\n�޸�[%s]ʧ�ܣ�\n", cMessage);
	}

	Pause();
}

static void StartedProject(void) {
	SetColor(BRIGHT_CYAN);
	puts("\n��ǰ�������޸���Ŀ\n");

	SetColor(BRIGHT_MAGENTA);

	BOOL bSign = FALSE;
	if (g_bIsBackStageRun) {
		puts("ȡ����̨����������");
		bSign = TRUE;
	}
	if (g_bIsAnyPosition) {
		puts("�ص����ù���������");
		bSign = TRUE;
	}
	if (g_bIsLittleZombie) {
		puts("С��ʬ��Ч������");
		bSign = TRUE;
	}

	if (!bSign) {
		puts("Ŀǰû���޸���Ŀ��������");
	}

	Pause();
}