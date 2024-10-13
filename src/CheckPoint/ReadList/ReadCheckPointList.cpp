#include "ReadCheckPointList.h"

//定義
const char CHECKPOINT_TEXT_PATH[] = { "data/File/CheckPoint/CheckPoint.txt" };		//テキストデータのパス

void CReadCheckPointList::ReadFile()
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, CHECKPOINT_TEXT_PATH, "r") == 0) {
		//ファイルの読み込み、変数への保存
		while (fscanf_s(fp, "%d, %f,%f,%f , %f,%f,%f, %d,%d,%d,%d, %f",
			&m_CheckPointData.m_iCPNum,
			&m_CheckPointData.m_vPos.x, &m_CheckPointData.m_vPos.y, &m_CheckPointData.m_vPos.z,
			&m_CheckPointData.m_vSize.x, &m_CheckPointData.m_vSize.y, &m_CheckPointData.m_vSize.z,
			&m_CheckPointData.m_NextCPNum[0], &m_CheckPointData.m_NextCPNum[1], &m_CheckPointData.m_NextCPNum[2], &m_CheckPointData.m_NextCPNum[3],
			&m_CheckPointData.fRad
		) != EOF) {
			//リストに追加
			checkPointList.push_back(m_CheckPointData);
		}
	}

	fclose(fp);
}