#include "ReadParkourObjectList.h"

#define PARKOUR_LIST_PATH ("data/File/ParkourObject/ParkourObject.txt")

void ReadParkourObjectList::ReadFile()
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, PARKOUR_LIST_PATH, "r") == 0) {
		//ファイルの読み込み、変数への保存
		while (fscanf_s(fp, "%d,%f,%f,%f,%d", 
			m_sParkourData.m_eType,
			m_sParkourData.m_vObjectPos.x, m_sParkourData.m_vObjectPos.y, m_sParkourData.m_vObjectPos.z,
			m_sParkourData.m_IsAllive
		) != EOF) {
			//リストに追加
			sparkourObjectInfoList.push_back(m_sParkourData);
		}
	}

	fclose(fp);
}