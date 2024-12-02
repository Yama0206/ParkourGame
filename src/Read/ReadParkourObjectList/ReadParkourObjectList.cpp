#include "ReadParkourObjectList.h"

#define PARKOUR_LIST ("")

void ReadParkourObjectList::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, PARKOUR_LIST, "r");

	while (true) {
		//1行目は使わないので先に読み込みだけ済ませる
		/*fgets();*/

		//数値の読み込み
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %d",);

		//「,」を飛ばすために読み込み実行
		char c = fgetc(fp);
	}


	fclose(fp);
}