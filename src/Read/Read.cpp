#include "Read.h"

//初期化
void CRead::Init()
{
	memset(&m_Test, 0.0, sizeof(m_Test));


	//X
	for (int X = 0; X < MAP_CHIP_X_NUM; X++)
	{
		//Y
		for (int Y = 0; Y < MAP_CHIP_Y_NUM; Y++)
		{
			//m_FileReadMapData[Y][X] = 0;
		}
	}
}


//読み込み
void CRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, "Data/Map/マップチップ.txt", "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	int resurt = 0;

	while (true) {
		//1行目は使わないので先に読み込みだけ済ませる
		/*fgets();*/

		//数値の読み込み
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %d", &eType, &m_Test.m_vPos.x, &m_Test.m_vPos.y, &m_Test.m_vPos.z, &m_Test.m_vSize.x, &m_Test.m_vSize.y, &m_Test.m_vSize.z, &eType);

		//「,」を飛ばすために読み込み実行
		char c = fgetc(fp);
	}


	fclose(fp);
}

//ファイルの書き込み
void CRead::SaveFile()
{
	//ファイル構造体宣言
	FILE* fp;
	//ファイルを開く
	fopen_s(&fp, "Data/Map/マップチップ.csv", "a");

	if (fp != NULL) {
		int mapIndexX = 0;
		int mapIndexY = 0;

		while (true) {
			//数値の読み込み
	//

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
				fprintf_s(fp, "\n");
			}
			//改行でも読み込み終了でもなかったらプラス
			else
			{
				mapIndexX++;
			}

		}
	}

}

//描画
void CRead::Draw()
{
	int t = eType;

	DrawFormatString(32, 32,GetColor(255, 0, 0), "%d, %f, %f, %f, %f, %f, %f, %d", &t, m_Test.m_vPos.x, m_Test.m_vPos.y, m_Test.m_vPos.z, m_Test.m_vSize.x, m_Test.m_vSize.y, m_Test.m_vSize.z, &t, true);
}
