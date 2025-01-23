#include "ReadItemList.h"

//定義
const char ITEM_TXT_PATH[] = { "data/File/Item/Item.txt" };

void CReadItemList::ReadFile()
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, ITEM_TXT_PATH, "r") == 0) {
		//ファイルの読み込み、変数への保存
		while (fscanf_s(fp, "%d, %f,%f,%f , %f,%f,%f , %f,%f,%f , %f,%f,%f, %d",
			&m_sItemData.m_eType,
			&m_sItemData.m_vPos.x, &m_sItemData.m_vPos.y, &m_sItemData.m_vPos.z,
			&m_sItemData.m_vScale.x, &m_sItemData.m_vScale.y, &m_sItemData.m_vScale.z,
			&m_sItemData.m_vRot.x, &m_sItemData.m_vRot.y, &m_sItemData.m_vRot.z,
			&m_sItemData.m_vSize.x, &m_sItemData.m_vSize.y, &m_sItemData.m_vSize.z,
			&m_sItemData.m_IsAllive
		) != EOF) {
			//リストに追加
			itemInfoList.push_back(m_sItemData);
		}
	}

	fclose(fp);
}

