#include "public_header.h"

#include "Plants vs. Zombies modifier.h"
#include "process.h"
#include "message.h"

#include <string.h>

const char* VERSION			= "0.03";							//当前修改器版本
const char* PROCESS_NAME	= "PlantsVsZombies.exe";			//游戏进程名

int main(void) {
	Init();													//对程序进行初始化操作
	
	while (TRUE) {											//建立消息循环
		Menu();
		Select();

		getchar();
	}
	
	return EXIT_FAILURE;									//非正常退出
}