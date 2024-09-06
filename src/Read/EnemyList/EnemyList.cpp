#include "EnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, ENEMY_TXT_PATH, "r");

	int EnemyIndex = 0;

	while (true) {
		//1行目は使わないので先に読み込みだけ済ませる
		/*fgets();*/

		//数値の読み込み
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f", m_sEnemy[EnemyIndex].m_eType ,
															   m_sEnemy[EnemyIndex].m_vPos.x, m_sEnemy[EnemyIndex].m_vPos.y, m_sEnemy[EnemyIndex].m_vPos.z,
															   m_sEnemy[EnemyIndex].m_vSize.x, m_sEnemy[EnemyIndex].m_vSize.y, m_sEnemy[EnemyIndex].m_vSize.z,
															   m_sEnemy[EnemyIndex].m_vRot.x, m_sEnemy[EnemyIndex].m_vRot.y, m_sEnemy[EnemyIndex].m_vRot.z);

		//「,」を飛ばすために読み込み実行
		char c = fgetc(fp);

		//EOFの場合は読み込み終了
		if (c == EOF) {
			break;
		}

		//改行コードの場合は保存先を変更する
		if (c == '\n') {
			EnemyIndex++;
		}
	}

	fclose(fp);
}