/*Game Message*/

#include "headgr.h"

extern BOOL isRun;
extern BOOL backStageRun;
extern BOOL anyPosition;
extern BOOL isLittle; 

/*主菜单*/
void menu(void){
	setColor(15);
	printf("\n————————————————————\n");
	printf("【植物大战僵尸】 C语言修改器\n\n");
	printf("O：重新打开/搜索进程\n");
	if(isRun){
		#if DEBUG
			printf("T：测试代码（Debug）\n");
		#endif
		printf("\na：常规修改：\n");
		printf("1：修改阳光\n");
		printf("2：修改金钱\n");
		printf("3：卡牌全部无冷却时间\n");
		printf("4：允许后台运行（再开一次取消）\n");
		printf("5：修改卡槽格数\n");
		printf("6：自动收集资源\n");

		printf("\nb：关卡修改：\n");
		printf("1：冒险模式跳关\n");
		printf("2：小游戏跳关（混乱关卡）\n");

		printf("\nc：植物修改：\n");
		printf("1：激活重叠放置（再开一次取消）\n");
		printf("2：紫卡种植无限制\n");

		printf("\nd：僵尸修改：\n");
		printf("1：秒杀场上所有僵尸\n");
		printf("2：小僵尸特效（再开一次恢复正常大小）\n");

		printf("\ne：花园修改：\n");
		printf("1：修改智慧树高度\n");
		printf("2：巧克力数量修改\n");

		printf("\nf：其他修改：\n");
		printf("1：花瓶透视\n");
		printf("2：显示隐藏小游戏\n");
	}
	printf("\n特殊功能：\n");
	printf("~：查看修改器更新公告\n");
	printf("!：查看迷你小游戏、解密模式、生存模式关卡代码\n");
	printf("@：查看PVZ小代码（彩蛋）大全\n");
	printf("#：查看目前已经开启的效果\n");
	printf("A：关于本修改器信息\n");
	printf("\nE：退出修改器");
	printf("\n————————————————————\n");
}

/*更新信息*/
void upData(void){
	setColor(9);
	printf("\n更新公告\n\n");
	printf("v0.1 [2019.03.04] 增加了最初的十个功能（1~0）\n");
	
	printf("v0.2 [2019.03.13] 新增以下功能：\n");
	printf("\t(1)自动收集资源\n\t(2)显示隐藏小游戏\n\t(3)重叠放置\n\t(4)巧克力修改\n\t(5)小僵尸特效\n\t(6)紫卡种植无限制\n");
	printf("修复/增强了以下功能：\n");
	printf("\t(1)花瓶透视不稳定性修复\n\t(2)秒杀僵尸不稳定性修复\n");
	
	printf("v0.21 [2019.07.28] 优化内存读写操作\n");
	
	printf("v0.22 [2019.09.16] 优化文件结构\n");
	
	pause();
}

/*小代码*/
void cheatCode(void){
	setColor(5);
	printf("\nPVZ小代码大全（培养智慧树到一定高度智慧树会告诉你的）\n\n");
	printf("future ------ 僵尸戴上时尚太阳眼镜\n");
	printf("mustache ---- 僵尸戴上两撇胡子\n");
	printf("trickedout -- 剪草机统一变成机车剪草机\n");
	printf("daisies ----- 当僵尸被杀后掉下一些雏菊（需要智慧树达到100米）\n");
	printf("dance ------- 让僵尸摆动身体跳舞（动次打次 动次打次）（需要智慧树达到500米）\n");
	printf("sukhbir ----- 切换僵尸呼唤大脑时的叫声φ(>ω<*) \n");
	printf("pinata ------ 僵尸死后散落一地的糖果（需要智慧树达到1000米）\n");
	
	pause();
}

/*显示迷你游戏列表*/
void showMiniGameList(void){
	setColor(11);
	
	printf("\n小游戏代码（红色加“*”标志的关卡不能跳关/混乱，会造成崩溃退出）\n\n");
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
	
	int i;
	int gameLength=sizeof(MiniGame)/sizeof(MiniGame[0]);
	for(i=0;i<gameLength;i++){
		if(i==37||i==42||i==49){
			setColor(12);
			printf("*");
		}else{
			setColor(11);
		}
		printf("%d.%s\n",i+1,MiniGame[i]);
	}
	
	pause();
}

/*暂停*/
void pause(void){
	setColor(14);
	printf("\n按任意键继续……\n");
	
	getch();
}

/*找不到操作*/
void noOperation(void){
	setColor(14);
	printf("\n找不到相关操作！请重新输入操作按键！\n");
	
	pause();
}

/*关于信息*/
void about(void){
	printf("\n关于：本程序是植物大战僵尸（Plants vs. Zombies）的修改器，使用【Dev-C++】开发编译");
	printf("\n修改器作者：流水“渺渺\n感谢大家的使用，有任何疑问和bug可以反馈给我\n\n");
	
	pause();
}

/*显示修改提示信息*/
void cheatMsg(BOOL isSuccess,const char msg[]){
	if(isSuccess){
		setColor(10);
		printf("\n修改【%s】成功！\n",msg);
	}else{
		setColor(12);
		printf("\n修改【%s】失败！\n",msg);
	}
	
	pause();
}

/*显示启动的修改项目*/
void showOpenCheat(void){
	setColor(11);
	printf("\n当前开启的修改项目\n\n");
	
	setColor(13);
	
	BOOL sign=FALSE;
	if(backStageRun){
		printf("取消后台功能已启用\n");
		sign=TRUE;
	}
	if(anyPosition){
		printf("重叠放置功能已启用\n");
		sign=TRUE;
	}
	if(isLittle){
		printf("小僵尸特效已启用\n");
		sign=TRUE;
	}
	
	if(!sign)printf("目前没有修改项目正在启动\n");
	
	pause();
}

/*显示进程名称*/
void showProcessName(const char msg1[],const char msg2[]){
	printf("%s",msg1);
	printf(PROCESS_NAME);
	printf("%s",msg2);
}
 
