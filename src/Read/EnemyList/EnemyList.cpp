#include "EnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, ENEMY_TXT_PATH, "r") == 0) {
		//ファイルの読み込み、変数への保存
		while (fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f",
			&m_sEnemyData.m_eType,
			&m_sEnemyData.m_vPos.x, &m_sEnemyData.m_vPos.y, &m_sEnemyData.m_vPos.z,
			&m_sEnemyData.m_vSize.x, &m_sEnemyData.m_vSize.y, &m_sEnemyData.m_vSize.z,
			&m_sEnemyData.m_vRot.x, &m_sEnemyData.m_vRot.y, &m_sEnemyData.m_vRot.z,
			&m_sEnemyData.m_vSpeed.x, &m_sEnemyData.m_vSpeed.y, &m_sEnemyData.m_vSpeed.z
		) != EOF) {
			//リストに追加
			enemyInfoList.push_back(m_sEnemyData);
		}
	}

	fclose(fp);
}