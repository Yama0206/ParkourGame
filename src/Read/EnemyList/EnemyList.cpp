#include "EnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, ENEMY_TXT_PATH, "r");

	int EnemyIndex = 0;

	while (true) {
		//1�s�ڂ͎g��Ȃ��̂Ő�ɓǂݍ��݂����ς܂���
		/*fgets();*/

		int a = 0;

		//���l�̓ǂݍ���
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %f", 
				&m_sEnemy[EnemyIndex].m_eType,
				&m_sEnemy[EnemyIndex].m_vPos.x,	 &m_sEnemy[EnemyIndex].m_vPos.y,  &m_sEnemy[EnemyIndex].m_vPos.z,
				&m_sEnemy[EnemyIndex].m_vSize.x, &m_sEnemy[EnemyIndex].m_vSize.y, &m_sEnemy[EnemyIndex].m_vSize.z,
				&m_sEnemy[EnemyIndex].m_vRot.x , &m_sEnemy[EnemyIndex].m_vRot.y,  &m_sEnemy[EnemyIndex].m_vRot.z,
				&m_sEnemy[EnemyIndex].m_vSpeed.x, &m_sEnemy[EnemyIndex].m_vSpeed.y, &m_sEnemy[EnemyIndex].m_vSpeed.z,
				&m_sEnemy[EnemyIndex].m_iHndl, &m_sEnemy[EnemyIndex].m_bIsActive, m_sEnemy[EnemyIndex].m_fRadius);

		//�u,�v���΂����߂ɓǂݍ��ݎ��s
		char c = fgetc(fp);

		//EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (c == EOF) {
			break;
		}

		//���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (c == '\n') {
			EnemyIndex++;
		}
	}

	fclose(fp);
}