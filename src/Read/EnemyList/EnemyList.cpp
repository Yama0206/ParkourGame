#include "EnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, ENEMY_TXT_PATH, "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	int resurt = 0;

	while (true) {
		//1行目は使わないので先に読み込みだけ済ませる
		/*fgets();*/

		//数値の読み込み
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f", );

		//「,」を飛ばすために読み込み実行
		char c = fgetc(fp);

		//EOFの場合は読み込み終了
		if (c == EOF) {
			break;
		}

		//改行コードの場合は保存先を変更する
		if (c == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
		//改行でも読み込み終了でもなかったらプラス
		else
		{
			mapIndexX++;
		}

	}

	fclose(fp);
}