/*Game Message*/

#include "header\g_msg.h"

/*主菜单*/
void menu(void){
	setColor(BRIGHT_WHITE);
	puts("\n————————————————————");
	puts("【植物大战僵尸】 C语言修改器\n");
	puts("O：重新打开/搜索进程\n");
	if(g_bIsRun){
		#if DEBUG
			puts("T：测试代码（Debug）\n");
		#endif
		puts("a：常规修改：");
		puts("1：修改阳光");
		puts("2：修改金钱");
		puts("3：卡牌无冷却时间");
		puts(g_bIsBackStageRun?"4：取消后台运行":"4：允许后台运行");
		puts("5：修改卡槽格数");
		puts("6：自动收集资源\n");

		puts("b：关卡修改：");
		puts("1：冒险模式跳关");
		puts("2：小游戏跳关（混乱关卡）\n");

		puts("c：植物修改：");
		puts(g_bIsAnyPosition?"1：取消重叠放置":"1：激活重叠放置");
		puts("2：紫卡种植无限制\n");

		puts("d：僵尸修改：");
		puts("1：秒杀场上所有僵尸");
		puts(g_bIsLittleZombie?"2：关闭小僵尸特效\n":"2：开启小僵尸特效\n");

		puts("e：花园修改：");
		puts("1：修改智慧树高度");
		puts("2：巧克力数量修改\n");

		puts("f：其他修改：");
		puts("1：花瓶透视");
		puts("2：显示隐藏小游戏\n");
	}
	puts("特殊功能：");
	puts("~：查看修改器更新公告");
	puts("!：查看迷你小游戏、解密模式、生存模式关卡代码");
	puts("@：查看PVZ小代码（彩蛋）大全");
	puts("#：查看目前已经开启的效果");
	puts("A：关于本修改器信息\n");
	puts("E：退出修改器\n");
	puts("————————————————————");
}

/*更新信息*/
void upDate(void){
	setColor(BRIGHT_BLUE);
	puts("\n更新公告\n");
	puts("v0.1 [2019.03.04] 增加了最初的十个功能（1~0）");
	
	puts("v0.2 [2019.03.13] 新增以下功能：");
	puts("\t(1)自动收集资源\n\t(2)显示隐藏小游戏\n\t(3)重叠放置\n\t(4)巧克力修改\n\t(5)小僵尸特效\n\t(6)紫卡种植无限制");
	puts("修复/增强了以下功能：");
	puts("\t(1)花瓶透视不稳定性修复\n\t(2)秒杀僵尸不稳定性修复");
	
	puts("v0.21 [2019.07.28] 优化内存读写操作");
	
	puts("v0.22 [2019.09.16] 优化文件结构");
	
	pause();
}

/*小代码*/
void cheatCode(void){
	setColor(MAGENTA);
	puts("\nPVZ小代码大全（培养智慧树到一定高度智慧树会告诉你的）\n");
	puts("future ------ 僵尸戴上时尚太阳眼镜");
	puts("mustache ---- 僵尸戴上两撇胡子");
	puts("trickedout -- 剪草机统一变成机车剪草机");
	puts("daisies ----- 当僵尸被杀后掉下一些雏菊（需要智慧树达到100米）");
	puts("dance ------- 让僵尸摆动身体跳舞（动次打次 动次打次）（需要智慧树达到500米）");
	puts("sukhbir ----- 切换僵尸呼唤大脑时的叫声φ(>ω<*)");
	puts("pinata ------ 僵尸死后散落一地的糖果（需要智慧树达到1000米）");
	
	pause();
}

/*显示迷你游戏列表*/
void showMiniGameList(void){
	setColor(BRIGHT_CYAN);
	
	puts("\n小游戏代码（红色加“*”标志的关卡不能跳关/混乱，会造成崩溃退出）\n");
	const char *miniGameList[]={"生存模式：白天","生存模式：黑夜","生存模式：泳池","生存模式：浓雾","生存模式：屋顶",
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

/*找不到操作*/
void noOperation(void){
	setColor(BRIGHT_YELLOW);
	puts("\n找不到相关操作！请重新输入操作按键！");
	
	pause();
}

/*关于信息*/
void about(void){
	puts("\n关于：本程序是植物大战僵尸（Plants vs. Zombies）的修改器，使用【Dev-C++】开发编译");
	puts("修改器作者：流水“渺渺\n感谢大家的使用，有任何疑问和bug可以反馈给我");
	
	pause();
}

/*显示修改提示信息*/
void cheatMsg(BOOL bIsSuccess,const char cMsg[]){
	if(bIsSuccess){
		setColor(BRIGHT_GREEN);
		printf("\n修改【%s】成功！\n",cMsg);
	}else{
		setColor(BRIGHT_RED);
		printf("\n修改【%s】失败！\n",cMsg);
	}
	
	pause();
}

/*显示启动的修改项目*/
void showOpenCheat(void){
	setColor(BRIGHT_CYAN);
	puts("\n当前开启的修改项目\n");
	
	setColor(BRIGHT_MAGENTA);
	
	BOOL bSign=FALSE;
	if(g_bIsBackStageRun){
		puts("取消后台功能已启用");
		bSign=TRUE;
	}
	if(g_bIsAnyPosition){
		puts("重叠放置功能已启用");
		bSign=TRUE;
	}
	if(g_bIsLittleZombie){
		puts("小僵尸特效已启用");
		bSign=TRUE;
	}
	
	if(!bSign){
		puts("目前没有修改项目正在启动");
	}
	
	pause();
}

/*显示进程名称*/
void showProcessName(const char cMsgFirst[],const char cMsgLast[]){
	printf("%s%s%s",cMsgFirst,PROCESS_NAME,cMsgLast);
}
