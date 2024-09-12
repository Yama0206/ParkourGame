#include "ItemList.h"

//��`
const char ITEM_TXT_PATH[] = { "data/File/Item.txt" };

void CItemList::ReadFile()
{
	FILE* fp = nullptr;

	//�t�@�C�����J��
	if (fopen_s(&fp, ITEM_TXT_PATH, "r") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		while (fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f",
			&m_sItemData.m_eType,
			&m_sItemData.m_vPos.x, &m_sItemData.m_vPos.y, &m_sItemData.m_vPos.z,
			&m_sItemData.m_vScale.x, &m_sItemData.m_vScale.y, &m_sItemData.m_vScale.z,
			&m_sItemData.m_vRot.x, &m_sItemData.m_vRot.y, &m_sItemData.m_vRot.z
		) != EOF) {
			//���X�g�ɒǉ�
			itemInfoList.push_back(m_sItemData);
		}
	}

	fclose(fp);
}