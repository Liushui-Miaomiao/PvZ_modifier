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
	puts("\n——————————————————————————");
	puts("【植物大战僵尸】 C语言修改器\n");
	puts("O：重新打开/搜索进程\n");
	if (g_bGameIsRun) {
		SetColor(BRIGHT_CYAN);
		puts("a：常规修改：\t\t\tb：关卡修改：");
		SetColor(BRIGHT_WHITE);
		puts("1：修改阳光\t\t\t1：冒险模式跳关");
		puts("2：修改金钱\t\t\t2：小游戏跳关（混乱关卡）");
		puts("3：卡牌无冷却时间");
		puts(g_bIsBackStageRun ? "4：取消后台运行" : "4：允许后台运行");
		puts("5：修改卡槽格数");
		puts("6：自动收集资源\n");

		SetColor(BRIGHT_CYAN);
		puts("c：植物修改：\t\t\td：僵尸修改：");
		SetColor(BRIGHT_WHITE);
		printf("%s\t\t\t1：秒杀场上所有僵尸\n", g_bIsAnyPosition ? "1：取消重叠放置" : "1：激活重叠放置");
		printf("2：紫卡种植无限制\t\t%s\n", g_bIsLittleZombie ? "2：关闭小僵尸特效\n" : "2：开启小僵尸特效\n");

		SetColor(BRIGHT_CYAN);
		puts("e：花园修改：\t\t\tf：其他修改：");
		SetColor(BRIGHT_WHITE);
		puts("1：修改智慧树高度\t\t1：花瓶透视");
		puts("2：巧克力数量修改\t\t2：显示隐藏小游戏\n");
	}
	SetColor(BRIGHT_CYAN);
	puts("特殊功能：");
	SetColor(BRIGHT_WHITE);
	puts("~：查看修改器更新公告\t\t!：查看关卡代码");
	puts("@：查看PVZ小代码大全\t\t#：查看已经开启的效果");
	puts("A：关于本修改器信息\t\tE：退出修改器\n");
	puts("——————————————————————————");
}

void Select(void) {
	SetColor(BRIGHT_YELLOW);
	printf("请选择要进行的操作：");
	char l_iCommand = 0;
	scanf_s("%c", &l_iCommand, 1);
	//printf("%d", l_iCommand);

	SetColor(BRIGHT_MAGENTA);
	switch (l_iCommand) {
	case 'O':
		g_bGameIsRun = OpenGameProcess();
		break;
	case 'a':																//各类选择分支判断
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		if (!g_bGameIsRun) {												//如果处于未运行状态
			SetColor(BRIGHT_YELLOW);
			puts("\n请先打开修改器搜索游戏句柄！");

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
	puts("\n找不到相关操作！");

	Pause();
}

static void BranchUniversal(void) {
	printf("\n已进入[常规修改]菜单，请选择要进行的操作：");
	int l_iCommand = getchar();
	SetColor(BRIGHT_MAGENTA);

	switch (l_iCommand) {
	case '1':
		printf("\n请输入要修改的阳光数量：");
		scanf_s("%d",p_dwBuffer);
		ExecutionInformation(ChangeSunLight(),"阳光");
		break;
	case '2':
		printf("\n请输入要修改的金钱数量：");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeMoney(), "金钱");
		break;
	case '3':
		ExecutionInformation(CardNoCD(), "卡牌无冷却");
		break;
	case '4':
		ExecutionInformation(AllowBackStageRun(!g_bIsBackStageRun), g_bIsBackStageRun ? "恢复后台" : "取消后台");
		g_bIsBackStageRun = !g_bIsBackStageRun;
		break;
	case '5':
		printf("\n请输入要修改的卡槽格数：");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeCardNum(), "卡槽格数");
		break;
	case '6':
		ExecutionInformation(AutoCollect(), "自动收集开启");
		break;
	default:
		OperationNotFound();
	}
}

static void BranchCheckpoint(void) {
	printf("\n已进入[关卡修改]菜单，请选择要进行的操作：");
	int l_iCommand = getchar();
	SetColor(BRIGHT_MAGENTA);

	switch (l_iCommand) {
	case '1':
		printf("\n请输入要修改的冒险关卡：");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(AdventureJumpLevel(), "冒险关卡");
		break;
	case '2':
		printf("\n请输入要进入的迷你游戏ID：");
		scanf_s("%d", p_dwBuffer);
		ExecutionInformation(ChangeMoney(), "金钱");
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
	puts("\n更新公告\n");
	puts("v0.1 [2019.03.04] 增加了最初的十个功能（1~0）");

	puts("v0.2 [2019.03.13] 新增以下功能：");
	puts("\t(1)自动收集资源\n\t(2)显示隐藏小游戏\n\t(3)重叠放置\n\t(4)巧克力修改\n\t(5)小僵尸特效\n\t(6)紫卡种植无限制");
	puts("修复/增强了以下功能：");
	puts("\t(1)花瓶透视不稳定性修复\n\t(2)秒杀僵尸不稳定性修复");
	puts("v0.21 [2019.07.28] 优化内存读写操作");
	puts("v0.22 [2019.09.16] 优化文件结构");

	puts("v0.3 [2020.06.25] 将Dev-CPP工程转为Microsoft Visual Studio工程。");

	Pause();
}

static void CheatCode(void) {
	SetColor(MAGENTA);
	puts("\nPVZ小代码大全（培养智慧树到一定高度智慧树会告诉你的）\n");
	puts("future ------ 僵尸戴上时尚太阳眼镜");
	puts("mustache ---- 僵尸戴上两撇胡子");
	puts("trickedout -- 剪草机统一变成机车剪草机");
	puts("daisies ----- 当僵尸被杀后掉下一些雏菊（需要智慧树达到100米）");
	puts("dance ------- 让僵尸摆动身体跳舞（动次打次 动次打次）（需要智慧树达到500米）");
	puts("sukhbir ----- 切换僵尸呼唤大脑时的叫声φ(>ω<*)");
	puts("pinata ------ 僵尸死后散落一地的糖果（需要智慧树达到1000米）");

	Pause();
}

static void ShowGameList(void) {
	SetColor(BRIGHT_CYAN);

	puts("\n小游戏代码（红色加“*”标志的关卡不能跳关/混乱，会造成崩溃退出）\n");
	const char* miniGameList[] = { "生存模式：白天","生存模式：黑夜","生存模式：泳池","生存模式：浓雾","生存模式：屋顶",
							"生存模式：白天（困难）","生存模式：黑夜（困难）","生存模式：泳池（困难）","生存模式：浓雾（困难）","生存模式：屋顶（困难）",
							"生存模式：白天（无尽）","生存模式：黑夜（无尽）","生存模式：泳池（无尽）","生存模式：浓雾（无尽）","生存模式：屋顶（无尽）",
							"植物僵尸","坚果保龄球模式","老虎机","雨中种植物","宝石迷阵",
							"隐形食脑者","看星星","僵尸水族馆","宝石迷阵转转看","小僵尸大麻烦",
							"保护传送门","你看，他们像柱子一样","雪橇区","僵尸快跑","锤僵尸",
							"谁笑到最后","植物僵尸2","坚果保龄球2","跳跳舞会","僵王博士的复仇",
							"坚果保龄球艺术锦标赛","晴天","无草皮之地（崩溃跳出，原因：少2道草皮）","重要时间","挑战种太阳花的艺术",
							"空袭","冰冻关卡","禅境花园（崩溃跳出）","超乎寻常的地心引力","坟墓模式",
							"你能把它挖出来吗","黑暗的暴风雨夜","蹦极闪电战","松鼠","智慧树（崩溃跳出）",
							"破罐者","全部留下","第三个罐子","连锁反应","M的意思是金属",
							"胆怯的制陶工","变戏法","另一个连锁反应","罐子王牌","无尽的试炼",
							"我是僵尸","我也是僵尸","你能铲了它么","完全傻了","死亡飞艇",
							"我烂了","僵尸摇摆","三连击","你的所有大脑都是属于我的","我是僵尸无尽版"
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
	puts("\n关于：本程序是植物大战僵尸（Plants vs. Zombies）的修改器");
	puts("使用【Microsoft Visual Studio】开发编译");
	puts("Author : Kujo Game Studio");
	puts("感谢大家的使用，有任何疑问和bug可以反馈给我");

	Pause();
}

static void ExecutionInformation(BOOL bIsSuccess, char* cMessage) {
	if (bIsSuccess) {
		SetColor(BRIGHT_GREEN);
		printf("\n修改[%s]成功！\n", cMessage);
	}
	else {
		SetColor(BRIGHT_RED);
		printf("\n修改[%s]失败！\n", cMessage);
	}

	Pause();
}

static void StartedProject(void) {
	SetColor(BRIGHT_CYAN);
	puts("\n当前开启的修改项目\n");

	SetColor(BRIGHT_MAGENTA);

	BOOL bSign = FALSE;
	if (g_bIsBackStageRun) {
		puts("取消后台功能已启用");
		bSign = TRUE;
	}
	if (g_bIsAnyPosition) {
		puts("重叠放置功能已启用");
		bSign = TRUE;
	}
	if (g_bIsLittleZombie) {
		puts("小僵尸特效已启用");
		bSign = TRUE;
	}

	if (!bSign) {
		puts("目前没有修改项目正在启动");
	}

	Pause();
}