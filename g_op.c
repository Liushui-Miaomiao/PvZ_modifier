/*Game Operation*/

#include "header\g_op.h"

/*初始化修改器*/
void initModifier(void){
	SetConsoleTitle("【植物大战僵尸】 C语言修改器 v0.22");
	
	p_g_dwBuffer=(DWORD *)malloc(sizeof(DWORD));
	
	g_hProcess=0;
	g_bIsBackStageRun=FALSE;
	g_bIsAnyPosition=FALSE;
	g_bIsLittleZombie=FALSE;
	g_bIsRun=openGameProcess();
}

/*循环事件*/
void loopEvent(void){
	menu();
	setColor(BRIGHT_YELLOW);
	
	printf("\n请按下按键选择选项：");
	g_iCommand=getchar();
	choice();
}

/*打开游戏进程*/
BOOL openGameProcess(void){
	setColor(BRIGHT_YELLOW);
	printf("正在打开进程...\n");
	
	if(getProcessPidByName(PROCESS_NAME,g_dwPid)){
		showProcessName("[","]");
		printf("[Pid：%d]\n",g_dwPid);
		
		g_hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,g_dwPid);
		
		if (g_hProcess!=0){
			setColor(BRIGHT_GREEN);
			showProcessName("\n成功打开游戏进程[","]！");
			printf("进程句柄：%d\n",g_hProcess);
			
			if(readMemory(g_hProcess,0x42748E,0,4)==0xFF563DE8){
				if(readMemory(g_hProcess,0x0054EBEF,0,1)==0xFF563DC3){
					g_bIsBackStageRun=TRUE;
				}
				if(readMemory(g_hProcess,0x0040FE30,0,1)==0xFF563D81
				&&readMemory(g_hProcess,0x00438E40,0,1)==0xFF563DEB
				&&readMemory(g_hProcess,0x0042A2D9,0,1)==0xFF563D8D){
					
					g_bIsAnyPosition=TRUE;
				}
				if(readMemory(g_hProcess,0x00523ED5,0,1)==0xFF563DEB){
					g_bIsLittleZombie=TRUE;
				}
				
				return TRUE;
			}else{
				setColor(BRIGHT_YELLOW);
				puts("\n不支持的游戏版本！");
				return FALSE;
			}
		}else{
			setColor(BRIGHT_RED);
			showProcessName("\n打开游戏进程[","]失败！\n");
		}
	}else{
		setColor(BRIGHT_YELLOW);
		showProcessName("未找到游戏进程：","\n");
	}
	
	return FALSE;
}

/*是否已经读取游戏进程*/
BOOL openModifier(void){
	if(!g_bIsRun){
		setColor(BRIGHT_YELLOW);
		printf("\n请先打开修改器搜索游戏句柄！\n");
	}
	
	return g_bIsRun;
}

/*选择流程*/
void choice(void){
	setColor(BRIGHT_MAGENTA);
	/*流程判断*/
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
		
		/*常规修改*/
		case 'a':
			choiceBranch("常规修改");
			break;
		
		/*关卡修改*/
		case 'b':
			choiceBranch("关卡修改");
			break;
		
		/*植物修改*/
		case 'c':
			choiceBranch("植物修改");
			break;
		
		/*僵尸修改*/
		case 'd':
			choiceBranch("僵尸修改");
			break;
		
		/*花园修改*/
		case 'e':
			choiceBranch("花园修改");
			break;
		
		/*其他修改*/
		case 'f':
			choiceBranch("其他修改");
			break;
		case '~':
			upDate();
			break;
		case '!':
			showMiniGameList();
			break;
		case '@':
			cheatCode();
			break;
		case '#':
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
	
	/*暂缓输入*/
	getchar();
}

/*选择分支*/
void choiceBranch(const char branceName[]){
	if(!openModifier()){
		pause();
		return;
	}
	
	getchar();
	setColor(BRIGHT_YELLOW);
	printf("\n已进入【%s】菜单，请选择子选项：",branceName);
	g_iCommand=getchar();
	setColor(BRIGHT_MAGENTA);
	
	if(!strcmp(branceName,"常规修改")){
		choiceBranchNormal();
	}else if(!strcmp(branceName,"关卡修改")){
		choiceBranchLevel();
	}else if(!strcmp(branceName,"植物修改")){
		choiceBranchPlant();
	}else if(!strcmp(branceName,"僵尸修改")){
		choiceBranchZombie();
	}else if(!strcmp(branceName,"花园修改")){
		choiceBranchGarden();
	}else{
		choiceBranchOther();
	}
}

/*选择分支 - 常规修改*/
void choiceBranchNormal(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n请输入要修改的阳光数量：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeSunlight(p_g_dwBuffer),"阳光");
			}
			break;
		case '2':
			if(openModifier()){
				printf("\n请输入要修改的金钱数量：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeMoney(p_g_dwBuffer),"金钱");
			}
			break;
		case '3':
			if(openModifier()){
				cheatMsg(cardNoCD(),"卡牌无冷却");
			}
			break;
		case '4':
			if(openModifier()){
				cheatMsg(backStageRun(g_bIsBackStageRun?0x57:0xC3),g_bIsBackStageRun?"恢复后台":"取消后台");
				g_bIsBackStageRun=!g_bIsBackStageRun;
			}
			break;
		case '5':
			if(openModifier()){
				printf("\n请输入要修改的卡槽格数（1~10）：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeCardsNum(p_g_dwBuffer),"卡槽格数");
			}
			break;
		case '6':
			if(openModifier()){
				cheatMsg(autoCollect(),"自动收集开启");
			}
			break;
		default :
			noOperation();
	}
}

/*选择分支 - 关卡修改*/
void choiceBranchLevel(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n请输入要修改的冒险关卡（例如我要去4-3关卡，那么应该输入43）：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(adventureJumpLevel(p_g_dwBuffer),"冒险模式关卡");
			}
			break;
		case '2':
			if(openModifier()){
				puts("\n需要先进入任意关卡然后点击菜单后");
				puts("（一定要这么做，否则会崩溃或者修改无效，此外重新开始会清除该模式下的存档，请注意备份存档），");
				puts("修改关卡代码然后点击重新开始，如果不重新开始的话将会产生混乱关卡的效果");
				printf("请输入要进入的迷你游戏ID（ID可通过查询【!】菜单的关卡代码（1~70））：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(miniGameJumpLevel(p_g_dwBuffer),"小游戏跳关");
			}
			break;
		default :
			noOperation();
	}
}

/*选择分支 - 植物修改*/
void choiceBranchPlant(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(anyPosition(g_bIsAnyPosition?0x84:0x81,
				g_bIsAnyPosition?0x74:0xEB,
				g_bIsAnyPosition?0x84:0x8D)
				,g_bIsAnyPosition?"取消重叠放置":"开启重叠放置");
				
				g_bIsAnyPosition=!g_bIsAnyPosition;
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(purpleUnlimit(),"紫卡种植无限制");
			}
			break;
		default :
			noOperation();
	}
}

/*选择分支 - 僵尸修改*/
void choiceBranchZombie(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(killAllZombies(),"秒杀全部僵尸");
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(littleZombie(g_bIsLittleZombie?0x74:0xEB)
				,g_bIsLittleZombie?"关闭小僵尸特效":"开启小僵尸特效");
				
				g_bIsLittleZombie=!g_bIsLittleZombie;
			}
			break;
		default :
			noOperation();
	}
}

/*选择分支 - 花园修改*/
void choiceBranchGarden(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				printf("\n请输入要修改的智慧树高度：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeWisdomTree(p_g_dwBuffer),"智慧树高度");
			}
			break;
		case '2':
			if(openModifier()){
				printf("\n请输入要修改的巧克力数量：");
				scanf("%d",p_g_dwBuffer);
				cheatMsg(changeChocolate(p_g_dwBuffer),"巧克力数量");
			}
			break;
		default :
			noOperation();
	}
}

/*选择分支 - 其他修改*/
void choiceBranchOther(void){
	switch(g_iCommand){
		case '1':
			if(openModifier()){
				cheatMsg(vaseFluoro(),"花瓶透视开启");
			}
			break;
		case '2':
			if(openModifier()){
				cheatMsg(showHideMiniGame(),"显示隐藏小游戏");
			}
			break;
		default :
			noOperation();
	}
}

/*规范数据范围*/
int limit(int iValue,int iMin,int iMax){
	if(iValue<iMin)return iMin;
	if(iValue>iMax)return iMax;
	
	return iValue;
}

/*暂停*/
void pause(void){
	setColor(BRIGHT_YELLOW);
	puts("\n按任意键继续……");
	
	getch();
}

/*阳光*/
BOOL changeSunlight(DWORD *p_dwSunlight){
	DWORD dwSunlight;
	dwSunlight=limit(*p_dwSunlight,0,9990);
	
	return writeMemory(g_hProcess,0x006A9EC0,2,dwSunlight,4,0x768,0x5560);
}

/*金钱*/
BOOL changeMoney(DWORD *p_dwMoney){
	DWORD dwMoney;
	dwMoney=limit(*p_dwMoney,0,99999);
	
	return writeMemory(g_hProcess,0x006A9EC0,2,dwMoney,4,0x82C,0x28);
}

/*卡牌无冷却*/
BOOL cardNoCD(void){
	return writeMemory(g_hProcess,0x00487296,0,0x1477,2);
}

/*后台运行*/
BOOL backStageRun(DWORD dwValue){
	return writeMemory(g_hProcess,0x0054EBEF,0,dwValue,1);
}

/*卡槽格数*/
BOOL changeCardsNum(DWORD *p_dwCardNum){
	DWORD dwCardNum;
	dwCardNum=limit(*p_dwCardNum,1,10);
	
	return writeMemory(g_hProcess,0x006A9EC0,3,dwCardNum,4,0x768,0x144,0x24);
}

/*自动收集*/
BOOL autoCollect(void){
	return writeMemory(g_hProcess,0x0043158F,0,0xEB,1);
}

/*冒险跳关*/
BOOL adventureJumpLevel(DWORD *p_dwLevel){
	DWORD dwLevel;
	dwLevel=limit(*p_dwLevel,11,99)-10;
	
	return writeMemory(g_hProcess,0x006A9EC0,2,dwLevel,4,0x82C,0x24);
}

/*小游戏跳关*/
BOOL miniGameJumpLevel(DWORD *p_dwLevel){
	DWORD dwLevel;
	dwLevel=limit(*p_dwLevel,1,70);
	
	return writeMemory(g_hProcess,0x006A9EC0,1,dwLevel,4,0x7F8);
}

/*重叠放置*/
BOOL anyPosition(DWORD dwValue_1,DWORD dwValue_2,DWORD dwValue_3){
	return writeMemory(g_hProcess,0x0040FE30,0,dwValue_1,1)
		&&writeMemory(g_hProcess,0x00438E40,0,dwValue_2,1)
		&&writeMemory(g_hProcess,0x0042A2D9,0,dwValue_3,1);
}

/*紫卡无限制*/
BOOL purpleUnlimit(void){
	return writeMemory(g_hProcess,0x0041D7D0,0,0xC301B0,3)
		&&writeMemory(g_hProcess,0x0040E477,0,0xEB,1);
}

/*秒杀全部僵尸*/
BOOL killAllZombies(void){
	int i;
	BOOL bKill=FALSE;
	printf("僵尸数量：%d\n",readMemory(g_hProcess,0x006A9EC0,2,4,0x768,0xA0));
	for(i=0;i<ZOMBIES_MAX_NUM;i++){
		if(readMemory(g_hProcess,0x006A9EC0,3,4,0x768,0x90,i*0x15C+0xEC)==ZOMBIES_NORMAL_STATUS){
			bKill=writeMemory(g_hProcess,0x006A9EC0,3,ZOMBIES_DIE_STATUS,4,0x768,0x90,i*0x15C+0x28);
		}
	}
	
	return bKill;
}

/*小僵尸特效*/
BOOL littleZombie(DWORD dwValue){
	return writeMemory(g_hProcess,0x00523ED5,0,dwValue,1);
}

/*智慧树*/
BOOL changeWisdomTree(DWORD *p_dwTreeHigh){
	DWORD dwTreeHigh;
	dwTreeHigh=limit(*p_dwTreeHigh,0,2147483647);
	
	return writeMemory(g_hProcess,0x006A9EC0,2,dwTreeHigh,4,0x82C,0xF4);
}

/*巧克力*/
BOOL changeChocolate(DWORD *p_dwChocolate){
	DWORD dwChocolate;
	dwChocolate=limit(*p_dwChocolate,0,999)+1000;
	
	return writeMemory(g_hProcess,0x006A9EC0,2,dwChocolate,4,0x82C,0x228);
}

/*花瓶透视*/
BOOL vaseFluoro(void){
	return writeMemory(g_hProcess,0x0044E5CC,0,0x0033B866,4);
}

/*显示隐藏小游戏*/
BOOL showHideMiniGame(void){
	return writeMemory(g_hProcess,0x0042DF5D,0,0x38,1);
}
