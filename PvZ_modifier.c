#include "header\PvZ_modifier.h"

/*main*/
int main(void){
	initModifier();
	
	while(TRUE){
		loopEvent();
	}
	
	return EXIT_FAILURE;
}
