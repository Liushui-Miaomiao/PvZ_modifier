#include "public_header.h"

#include "Plants vs. Zombies modifier.h"
#include "process.h"
#include "message.h"

#include <string.h>

const char* VERSION			= "0.03";							//��ǰ�޸����汾
const char* PROCESS_NAME	= "PlantsVsZombies.exe";			//��Ϸ������

int main(void) {
	Init();													//�Գ�����г�ʼ������
	
	while (TRUE) {											//������Ϣѭ��
		Menu();
		Select();

		getchar();
	}
	
	return EXIT_FAILURE;									//�������˳�
}