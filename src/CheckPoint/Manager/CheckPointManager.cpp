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
		cCheckPoint->SetInfo(m_cFileDataList.checkPointList[CheckPointIndex].m_eCP_Num,
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

void CCheckPointManager::AddCPNum()
{
	if (m_cCheckPointList[m_eCP_Num]->GetCPNum() >= Point_1 && m_cCheckPointList[m_eCP_Num]->GetCPNum() <= Point_2) {
		m_cCheckPointList[m_eCP_Num]->SetCPNum(Point_2);
	}
	else if (m_cCheckPointList[m_eCP_Num]->GetCPNum() <= Point_3)
	{
		m_cCheckPointList[m_eCP_Num]->SetCPNum(Point_3);
	}
	else if (m_cCheckPointList[m_eCP_Num]->GetCPNum() <= Point_4)
	{
		m_cCheckPointList[m_eCP_Num]->SetCPNum(Point_4);
	}
	else if (m_cCheckPointList[m_eCP_Num]->GetCPNum() <= Point_5)
	{
		m_cCheckPointList[m_eCP_Num]->SetCPNum(Point_5);
	}
}

void CCheckPointManager::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}