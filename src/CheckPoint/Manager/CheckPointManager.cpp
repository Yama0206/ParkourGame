#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

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
		cCheckPoint->SetInfo(m_cFileDataList.checkPointList[CheckPointIndex].m_iCPNum,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].m_vPos,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_vSize,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad);

			//アイテムのリストにpush_backする
		m_cCheckPointList.push_back(cCheckPoint);
	}
}

CCheckPointManager* CCheckPointManager::GetInstance()
{
	//まだ生成されていないなら
	if (m_Instance == NULL)
	{
		m_Instance = new CCheckPointManager();
	}

	return m_Instance;

}


//int CCheckPointManager::GetiCPNum(int iID)
//{
//	//チェックポイントの数分for文を回す
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//チェックポイントの番号と引数の番号が一致したら
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//一致した番号の座標を返す
//			return m_cCheckPointList[CheckPointIndex]->GetiCPNum();
//		}
//	}
//}

//VECTOR CCheckPointManager::GetPosVec(int iID)
//{
//	//チェックポイントの数分for文を回す
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//チェックポイントの番号と引数の番号が一致したら
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//一致した番号の座標を返す
//			return m_cCheckPointList[CheckPointIndex]->GetPosVec();
//		}
//	}
//}
//
//float CCheckPointManager::GetfRad(int iID)
//{
//	//チェックポイントの数分for文を回す
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//チェックポイントの番号と引数の番号が一致したら
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//一致した番号の座標を返す
//			return m_cCheckPointList[CheckPointIndex]->GetRad();
//		}
//	}
//}

void CCheckPointManager::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}