#include "ReadJumpObject.h"

constexpr char JUMPOBJECT_TEXT_PATH[] = { "data/File/Object/JumpObject" };

//void CReadJumpObject::ReadFile()
//{
//	FILE* fp = nullptr;
//
//	//�t�@�C�����J��
//	if (fopen_s(&fp, JUMPOBJECT_TEXT_PATH, "r") == 0) {
//		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
//		while (fscanf_s(fp, "%d, %f,%f,%f , %f,%f,%f , %f,%f,%f , %f,%f,%f, %d",
//			&m_sJumpObjectData.m_eType,
//			&m_sJumpObjectData.m_vPos.x, &m_sJumpObjectData.m_vPos.y, &m_sJumpObjectData.m_vPos.z,
//			&m_sJumpObjectData.m_vScale.x, &m_sJumpObjectData.m_vScale.y, &m_sJumpObjectData.m_vScale.z,
//			&m_sJumpObjectData.m_vRot.x, &m_sJumpObjectData.m_vRot.y, &m_sJumpObjectData.m_vRot.z,
//			&m_sJumpObjectData.m_vSize.x, &m_sJumpObjectData.m_vSize.y, &m_sJumpObjectData.m_vSize.z,
//			&m_sJumpObjectData.m_IsAllive
//		) != EOF) {
//			//���X�g�ɒǉ�
//			jumpobjectList.push_back(m_sJumpObjectData);
//		}
//	}
//
//	fclose(fp);
//}