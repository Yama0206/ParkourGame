#include "ReadParkourObjectList.h"

#define PARKOUR_LIST ("")

void ReadParkourObjectList::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, PARKOUR_LIST, "r");

	while (true) {
		//1�s�ڂ͎g��Ȃ��̂Ő�ɓǂݍ��݂����ς܂���
		/*fgets();*/

		//���l�̓ǂݍ���
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %d",);

		//�u,�v���΂����߂ɓǂݍ��ݎ��s
		char c = fgetc(fp);
	}


	fclose(fp);
}