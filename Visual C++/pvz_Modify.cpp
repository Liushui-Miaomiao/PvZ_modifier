/*植物大战僵尸C语言修改器*/

//是否为调试版本
#define isDebug 0

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "mod.h"

//游戏进程名称 
char processName[]="PlantsVsZombies.exe";
//用于获取输入命令的字符
char Command;
//定义进程PID
DWORD Pid;
//定义全局进程句柄
HANDLE hProcess=0;
//进程是否已经被打开
int isPro=0; 
//是否后台运行标识
int backStage=1;

//Timer
static BOOL TimerIsRun;
static BOOL TimerIsExit;
static DWORD TimerDelay;

/*函数声明*/
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

/*主函数*/
int main(){
	//设置程序标题 
	SetConsoleTitle("植物大战僵尸 C语言修改器 v0.1");
	//检测游戏进程
	isPro=openPro();
	
	while(1){
		menu();
		color(14);
		printf("\n请按下按键进行相应操作：");
		//接收输入的字符 
		Command=getchar();
		Choice();
		//暂缓输入 
		getchar();
	}
	return 0;
}

//打开进程
int openPro(){
	color(14);
	printf("正在打开进程...\n");
	
	//寻找进程名称并返回pid 
	if(FindProcessPid(processName,Pid)){
		printf("[%s][Pid：%d]\n",processName,Pid);
		hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
		if (hProcess!=0){
			color(10);
			printf("\n成功打开游戏进程[%s]！进程句柄：%d\n",processName,hProcess);
			return 1;
		}else{
			color(12);
			printf("\n打开游戏进程[%s]失败\n",processName);
		}
	}else{
		color(14);
		printf("未找到游戏进程：%s\n",processName);
	}
	return 0;
}

//修改器是否已经读入游戏进程 
int openMod(){
	if(hProcess==0){
		color(14);
		printf("\n请先打开修改器搜索游戏句柄！\n");
		return 0;
	}
	return 1;
}

//主菜单 
void menu(){
	color(15);
	printf("\n————————————————————\n");
	printf("植物大战僵尸C语言修改器\n\n");
	printf("O：重新打开/搜索进程[%s]\n",processName);
	if(isPro){
		#if isDebug
			printf("T：测试代码（Debug）\n");
		#endif
		printf("1：修改阳光\n");
		printf("2：修改金钱\n");
		printf("3：卡牌全部无冷却时间\n");
		printf("4：修改智慧树高度\n");
		printf("5：修改植物卡槽格数\n");
		printf("6：冒险模式跳关\n");
		printf("7：小游戏跳关\n");
		printf("8：允许后台运行（再开一次取消）\n");
		printf("9：秒杀场上所有僵尸（不太稳定）\n");
		printf("0：花瓶透视（当退出砸罐子模式后修改线程会自动退出）\n");
	}
	printf("\n特殊功能：\n");
	printf("！：查看迷你小游戏、解密模式、生存模式关卡代码\n");
	printf("@：查看PVZ作弊码（彩蛋）大全\n");
	printf("A：关于本修改器信息\n");
	printf("\nE：退出修改器");
	printf("\n————————————————————\n");
}

//判断选择
void Choice(){
	color(13);
	//根据字符判断应该执行什么流程 
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
				printf("\n当前值为：");
				writeMod_3(hProcess,0x006A9EC0,0x768,0x90,0x15C+0x28,3,4);
			}
			break;
		#endif
		case '1':
			if(openMod()){
				DWORD Sun;
				printf("\n请输入要修改的阳光数量：");
				scanf("%d",&Sun);
				if(Sun<0)Sun=0;
				if(Sun>9990)Sun=9990;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x768,0x5560,Sun,4),"阳光");
			}
			break;
		case '2':
			if(openMod()){
				DWORD Money;
				printf("\n请输入要修改的金钱数量：");
				scanf("%d",&Money);
				if(Money<0)Money=0;
				if(Money>99999)Money=99999;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x28,Money,4),"金钱");
			}
			break;
		case '3':
			if(openMod()){
				DWORD notCoolNum=0x1477;
				cheatMsg(WriteProcessMemory(hProcess,(LPVOID)0x00487296,&notCoolNum,2,NULL),"卡牌无冷却");
			} 
			break;
		case '4':
			if(openMod()){
				DWORD Tree;
				printf("\n请输入要修改的智慧树高度：");
				scanf("%d",&Tree);
				if(Tree<0)Tree=0;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0xF4,Tree,4),"智慧树高度");
			}
			break;
		case '5':
			if(openMod()){
				DWORD Card;
				printf("\n请输入要修改的卡槽格数（1~10）：");
				scanf("%d",&Card);
				if(Card<1)Card=1;
				if(Card>10)Card=10;
				cheatMsg(writeMod_3(hProcess,0x006A9EC0,0x768,0x144,0x24,Card,4),"卡槽格数");
			}
			break;
		case '6':
			if(openMod()){
				DWORD Checkpoint;
				printf("\n请输入要修改的冒险关卡（例如我要去4-3关卡，那么应该输入43）：");
				scanf("%d",&Checkpoint);
				if(Checkpoint<11)Checkpoint=11;
				Checkpoint-=10;
				cheatMsg(writeMod_2(hProcess,0x006A9EC0,0x82C,0x24,Checkpoint,4),"冒险模式关卡");
			}
			break;
		case '7':
			if(openMod()){
				DWORD MiniGame;
				printf("\n需要先进入任意关卡然后点击菜单后（一定要这么做，否则会崩溃或者修改无效，此外重新开始会清除该模式下的存档，请注意备份存档），修改关卡代码然后点击重新开始\n"); 
				printf("请输入要进入的迷你游戏ID（ID可通过查询【！】菜单的关卡代码（1~70））：");
				scanf("%d",&MiniGame);
				if(MiniGame<1)MiniGame=1;
				if(MiniGame>70)MiniGame=70;
				cheatMsg(writeMod_1(hProcess,0x006A9EC0,0x7F8,MiniGame,4),"小游戏跳关");
			}
			break;
		case '8':
			if(openMod()){
				DWORD cancelBackstage=0xc3;
				(backStage==1)?(cancelBackstage=0xC3):(cancelBackstage=0x57);
				cheatMsg(writeMod(hProcess,0x0054EBEF,cancelBackstage,1),backStage==1?"取消后台":"恢复后台");
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
				cheatMsg(kill,"秒杀全部僵尸");
			}
			break;
		case '0':
			if(openMod()){
				int sign;
				//先读取花瓶个数，如果是0个马上判定失败，调到失败语句 
				sign=ReadProcessMemory(hProcess,(LPVOID)getMemory_3(hProcess,0x006A9EC0,0x768,0x11C,0x4C,4),&sign,4,0);
				if(sign!=0){
					HANDLE hTimerThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TimerThread,NULL,0,NULL);
					if(!hTimerThread){
						color(12);
						fprintf(stderr,"\n修改线程创建失败！\n");
						pause();
					}
					//Timer运行间隔 
					TimerDelay=100;
				}
				cheatMsg(sign,"花瓶透视开启");
			}
			break;
		//~
		/*case '\x7E':
			if(openMod()){
				int zombieNum;
				
				printf("\n当前僵尸总数为：%d\n",zombieNum);
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
			printf("\n关于：本程序是植物大战僵尸（PlantsVsZombies）的修改器，使用Visual C++开发编译\n修改器作者：流水“渺渺\n感谢大家的使用，有任何疑问和bug可以反馈给我。\n\n");
			pause();
			break;
		default :
			color(14);
			printf("\n找不到相关操作！请重新输入操作按键！\n");
	}
} 

//修改信息 
void cheatMsg(int isSuccess,const char msg[10]){
	if(isSuccess){
		color(10);
		printf("\n修改%s成功！\n",msg);
	}else{
		color(12);
		printf("\n修改%s失败！\n",msg);
	}
	pause();
}

//暂停函数 
void pause(){
	color(14);
	printf("\n按任意键继续……\n");
	getch();
} 

//迷你游戏代码 
void showMiniGameList(){
	color(11);
	printf("\n小游戏代码\n\n");
	const char *MiniGame[]={"生存模式：白天","生存模式：黑夜","生存模式：泳池","生存模式：浓雾","生存模式：屋顶",
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
	
	int gameLen=sizeof(MiniGame)/sizeof(MiniGame[0]);
	int i;
	for(i=0;i<gameLen;i++){
		//标记出错关卡
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

//作弊码 
void cheatCode(){
	color(5);
	printf("\nPVZ作弊码大全（培养智慧树到一定高度智慧树会告诉你的）\n\n");
	printf("future ------ 僵尸戴上时尚太阳眼镜\n");
	printf("mustache ---- 僵尸戴上两撇胡子\n");
	printf("trickedout -- 剪草机统一变成机车剪草机\n");
	printf("daisies ----- 当僵尸被杀后掉下一些雏菊（需要智慧树达到100米）\n");
	printf("dance ------- 让僵尸摆动身体跳舞（动次打次 动次打次）（需要智慧树达到500米）\n");
	printf("sukhbir ----- 切换僵尸呼唤大脑时的叫声φ(>ω<*) \n");
	printf("pinata ------ 僵尸死后散落一地的糖果（需要智慧树达到1000米）\n");
	pause();
}

//时间线程 
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

//更改文字颜色
void color(int c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c); 
}
