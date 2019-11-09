#include "header\PvZ_modifier.h"

/*g_op - Game Operation*/
void initModifier(void);
void loopEvent(void);

/*main*/
int main(void){
	initModifier();
	
	while(TRUE){
		loopEvent();
	}
	
	return EXIT_FAILURE;
}
