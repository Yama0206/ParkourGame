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
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_NextCPNum);
		
		//配列の数分for分を回す
		for (int ArrayIndex = 0; ArrayIndex < NEXT_CHECKPOINT_NUM; ArrayIndex++)
		{
			//次に向かう場所が-1以外だったら次に迎える場所の数を+1する
			if (m_cFileDataList.checkPointList[CheckPointIndex].m_NextCPNum[ArrayIndex] != -1)
			{
				cCheckPoint->AddArayIndex();
			}
		}

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

void CCheckPointManager::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}