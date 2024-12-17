#include "ReadEnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp = nullptr;

	//�t�@�C�����J��
	if (fopen_s(&fp, ENEMY_TXT_PATH, "r") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		while (fscanf_s(fp, "%d, %f,%f,%f, %f,%f,%f, %f,%f,%f, %f,%f,%f, %d",
			&m_sEnemyData.m_eType,
			&m_sEnemyData.m_vPos.x, &m_sEnemyData.m_vPos.y, &m_sEnemyData.m_vPos.z,
			&m_sEnemyData.m_vScale.x, &m_sEnemyData.m_vScale.y, &m_sEnemyData.m_vScale.z,
			&m_sEnemyData.m_vRot.x, &m_sEnemyData.m_vRot.y, &m_sEnemyData.m_vRot.z,
			&m_sEnemyData.m_vSpeed.x, &m_sEnemyData.m_vSpeed.y, &m_sEnemyData.m_vSpeed.z,
			&m_sEnemyData.m_IsActive

		) != EOF) {
			//���X�g�ɒǉ�
			enemyInfoList.push_back(m_sEnemyData);
		}
	}

	fclose(fp);
}