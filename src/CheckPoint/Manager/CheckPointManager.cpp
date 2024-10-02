#include "CheckPointManager.h"

//定義
const int CHECKPOINT_NUM = 10;

CCheckPointManager::CCheckPointManager()
{
}

CCheckPointManager::~CCheckPointManager()
{

}

void CCheckPointManager::Load()
{
	m_cFileDataList.ReadFile();

	//モデルを複製
	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
			//情報を入れるクラスのポインタ変数を作成
		CCheckPoint* cCheckPoint = new CCheckPoint();

			//上で作ったクラスに情報を入力
		cCheckPoint->SetInfo(m_cFileDataList.checkPointList[CheckPointIndex].m_vPos,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_vSize,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad);

			//アイテムのリストにpush_backする
		m_cCheckPointList.push_back(cCheckPoint);
	}
}