#include "ReadObjectList.h"

void CObjectRead::ReadFile()
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, OBJECT_TXT_PATH, "r") == 0) {
		//ファイルの読み込み、変数への保存
		while (fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f",
			&m_sObject.m_eType,
			&m_sObject.m_vPos.x, &m_sObject.m_vPos.y, &m_sObject.m_vPos.z,
			&m_sObject.m_vSize.x, &m_sObject.m_vSize.y, &m_sObject.m_vSize.z,
			&m_sObject.m_vRot.x, &m_sObject.m_vRot.y, &m_sObject.m_vRot.z
		) != EOF) {
			//リストに追加
			objectInfoList.push_back(m_sObject);
		}
	}

	fclose(fp);
}