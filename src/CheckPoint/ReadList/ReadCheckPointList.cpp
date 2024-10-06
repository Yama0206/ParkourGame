#include "ReadCheckPointList.h"

//��`
const char CHECKPOINT_TEXT_PATH[] = { "data/File/CheckPoint.txt" };		//�e�L�X�g�f�[�^�̃p�X

void CReadCheckPointList::ReadFile()
{
	FILE* fp = nullptr;

	//�t�@�C�����J��
	if (fopen_s(&fp, CHECKPOINT_TEXT_PATH, "r") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		while (fscanf_s(fp, "%d, %f,%f,%f , %f,%f,%f, %f",
			&m_CheckPointData.m_iCPNum,
			&m_CheckPointData.m_vPos.x, &m_CheckPointData.m_vPos.y, &m_CheckPointData.m_vPos.z,
			&m_CheckPointData.m_vSize.x, &m_CheckPointData.m_vSize.y, &m_CheckPointData.m_vSize.z,
			&m_CheckPointData.fRad
		) != EOF) {
			//���X�g�ɒǉ�
			checkPointList.push_back(m_CheckPointData);
		}
	}

	fclose(fp);
}