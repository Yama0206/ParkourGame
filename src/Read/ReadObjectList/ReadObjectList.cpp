#include "ReadObjectList.h"

void CObjectRead::ReadFile()
{
	FILE* fp = nullptr;

	//�t�@�C�����J��
	if (fopen_s(&fp, OBJECT_TXT_PATH, "r") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		while (fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f",
			&m_sObject.m_eType,
			&m_sObject.m_vPos.x, &m_sObject.m_vPos.y, &m_sObject.m_vPos.z,
			&m_sObject.m_vSize.x, &m_sObject.m_vSize.y, &m_sObject.m_vSize.z,
			&m_sObject.m_vRot.x, &m_sObject.m_vRot.y, &m_sObject.m_vRot.z
		) != EOF) {
			//���X�g�ɒǉ�
			objectInfoList.push_back(m_sObject);
		}
	}

	fclose(fp);
}