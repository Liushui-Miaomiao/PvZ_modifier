/*Game Operation*/

#include "headgr.h"

extern DWORD g_dwPid;
extern HANDLE g_hProcess;
extern int g_iCommand;

extern BOOL g_bIsRun;
extern BOOL g_bIsBackStageRun;
extern BOOL g_bIsAnyPosition;
extern BOOL g_bIsLittleZombie; 

/*初始化修改器*/
void initModifier(void){
	SetConsoleTitle("【植物大战僵尸】 C语言修改器 v0.22");
	g_bIsRun=openGameProcess();
}

/*打开游戏进程*/
BOOL openGameProcess(void){
	setColor(BRIGHT_YELLOW);
	printf("正在打开进程...\n");
	
	//寻找进程名称并返回pid
	if(findProcessPidByName(PROCESS_NAME,g_dwPid)){
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
				if(readMemory(g_hProcess,0x0040FE30,0,1)==0xFF563D81&&readMemory(g_hProcess,0x00438E40,0,1)==0xFF563DEB&&readMemory(g_hProcess,0x0042A2D9,0,1)==0xFF563D8D){
					g_bIsAnyPosition=TRUE;
				}
				if(readMemory(g_hProcess,0x00523ED5,0,1)==0xFF563DEB){
					g_bIsLittleZombie=TRUE;
				}
				
				return TRUE;
			}else{
				setColor(BRIGHT_YELLOW);
				printf("\n不支持的游戏版本！\n");
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
	if(g_hProcess==0){
		setColor(BRIGHT_YELLOW);
		printf("\n请先打开修改器搜索游戏句柄！\n");
		return FALSE;
	}
	
	return TRUE;
}

/*选择流程*/
void choice(void){
	//缓冲区
	int l_iTempValue;
	
	setColor(BRIGHT_MAGENTA);
	//根据字符判断应该执行什么流程
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
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【常规修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n请输入要修改的阳光数量：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,9990);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x768,0x5560),"阳光");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n请输入要修改的金钱数量：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,99999);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x28),"金钱");
					}
					break;
				case '3':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x00487296,0,0x1477,2),"卡牌无冷却");
					break;
				case '4':
					if(openModifier()){
						if(!g_bIsBackStageRun){
							cheatMsg(writeMemory(g_hProcess,0x0054EBEF,0,0xC3,1),"取消后台");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x0054EBEF,0,0x57,1),"恢复后台");
						}
						g_bIsBackStageRun=!g_bIsBackStageRun;
					}
					break;
				case '5':
					if(openModifier()){
						printf("\n请输入要修改的卡槽格数（1~10）：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,1,10);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,3,l_iTempValue,4,0x768,0x144,0x24),"卡槽格数");
					}
					break;
				case '6':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0043158F,0,0xEB,1),"自动收集开启");
					break;
				default :
					noOperation();
			}
			break;
		
		/*关卡修改*/
		case 'b':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【关卡修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n请输入要修改的冒险关卡（例如我要去4-3关卡，那么应该输入43）：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,11,99)-10;
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x24),"冒险模式关卡");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n需要先进入任意关卡然后点击菜单后（一定要这么做，否则会崩溃或者修改无效，此外重新开始会清除该模式下的存档，请注意备份存档），");
						printf("修改关卡代码然后点击重新开始，如果不重新开始的话将会产生混乱关卡的效果\n");
						printf("请输入要进入的迷你游戏ID（ID可通过查询【!】菜单的关卡代码（1~70））：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,1,70);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,1,l_iTempValue,4,0x7F8),"小游戏跳关");
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*植物修改*/
		case 'c':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【植物修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						if(!g_bIsAnyPosition){
							cheatMsg(writeMemory(g_hProcess,0x0040FE30,0,0x81,1)&&writeMemory(g_hProcess,0x00438E40,0,0xEB,1)&&writeMemory(g_hProcess,0x0042A2D9,0,0x8D,1),"开启重叠放置");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x0040FE30,0,0x84,1)&&writeMemory(g_hProcess,0x00438E40,0,0x74,1)&&writeMemory(g_hProcess,0x0042A2D9,0,0x84,1),"取消重叠放置");
						}
						g_bIsAnyPosition=!g_bIsAnyPosition;
					}
					break;
				case '2':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0041D7D0,0,0xC301B0,3)&&writeMemory(g_hProcess,0x0040E477,0,0xEB,1),"紫卡种植无限制");
					break;
				default :
					noOperation();
			}
			break;
		
		/*僵尸修改*/
		case 'd':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【僵尸修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						int i;
						BOOL bKill=FALSE;
						printf("僵尸数量：%d\n",readMemory(g_hProcess,0x006A9EC0,2,4,0x768,0xA0));
						/*pvz最多有1024只僵尸*/
						for(i=0;i<1024;i++){
							if(readMemory(g_hProcess,0x006A9EC0,3,4,0x768,0x90,i*0x15C+0xEC)==0){
								bKill=writeMemory(g_hProcess,0x006A9EC0,3,3,4,0x768,0x90,i*0x15C+0x28);
							}
						}
						cheatMsg(bKill,"秒杀全部僵尸");
					}
					break;
				case '2':
					if(openModifier()){
						if(!g_bIsLittleZombie){
							cheatMsg(writeMemory(g_hProcess,0x00523ED5,0,0xEB,1),"开启小僵尸特效");
						}else{
							cheatMsg(writeMemory(g_hProcess,0x00523ED5,0,0x74,1),"关闭小僵尸特效");
						}
						g_bIsLittleZombie=!g_bIsLittleZombie;
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*花园修改*/
		case 'e':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【花园修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier()){
						printf("\n请输入要修改的智慧树高度：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,2147483647);
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0xF4),"智慧树高度");
					}
					break;
				case '2':
					if(openModifier()){
						printf("\n请输入要修改的巧克力数量：");
						scanf("%d",&l_iTempValue);
						l_iTempValue=limit(l_iTempValue,0,999)+1000;
						cheatMsg(writeMemory(g_hProcess,0x006A9EC0,2,l_iTempValue,4,0x82C,0x228),"巧克力数量");
					}
					break;
				default :
					noOperation();
			}
			break;
		
		/*其他修改*/
		case 'f':
			if(!openModifier()){
				pause();
				break;
			}
			
			getchar();
			setColor(BRIGHT_YELLOW);
			printf("\n已进入【其他修改】菜单，请选择子选项：");
			g_iCommand=getchar();
			setColor(BRIGHT_MAGENTA);
			switch(g_iCommand){
				case '1':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0044E5CC,0,0x0033B866,4),"花瓶透视开启");
					break;
				case '2':
					if(openModifier())cheatMsg(writeMemory(g_hProcess,0x0042DF5D,0,0x38,1),"显示隐藏小游戏");
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
	
	//暂缓输入
	getchar();
}

/*规范数据范围*/
int limit(int iValue,int iMin,int iMax){
	if(iValue<iMin)return iMin;
	if(iValue>iMax)return iMax;
	
	return iValue;
}
