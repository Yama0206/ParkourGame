#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

//定義
const int CHECKPOINT_NUM = 10;

CCheckPointManager::CCheckPointManager()
{
	//プレイヤーが通った場所
	memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));

	//プレイヤーが最後に通った場所
	m_iLastPassedPlayerNum = -1;
	//敵が最後に通った場所
	m_iLastPassedEnemyNum = -1;
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

void CCheckPointManager::Step()
{
	CDebugManager::GetInstance()->AddFormatString(400, 0, "敵が最後に通った場所 = %d", m_iLastPassedEnemyNum);
	CDebugManager::GetInstance()->AddFormatString(0, 200, "プレイヤーが通った場所を格納しているリストサイズ = %d", PLAYER_PASSED_LIST_SIZE);
	for (int i = 0; i < PLAYER_PASSED_LIST_SIZE; i++) {
		CDebugManager::GetInstance()->AddFormatString(0, 220+(i*20), "プレイヤーが通った場所%d番目 = %d", i,m_iPassedPlayerNum[i]);
	}
	CDebugManager::GetInstance()->AddFormatString(500, 600, "プレイヤーが通った場所を格納しているリストの今のサイズ = %d", CCheckPointManager::GetInstance()->GetPassedPlayerNumSize());
}

int CCheckPointManager::GetPassedPlayerNum()
{
	//配列の末尾を返したいので配列のサイズの最大値からfor文を回す
	for (int PassedPlayerIndex = PLAYER_PASSED_LIST_SIZE - 1; PassedPlayerIndex >= 0; PassedPlayerIndex++)
	{
		//通った場所が保存されているかどうか見つける
		if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
			//末尾の値を返す
			return m_iPassedPlayerNum[PassedPlayerIndex];
		}
		else {
			//何もなければ-1を返す
			return -1;
		}
	}
}

int CCheckPointManager::GetPassedPlayerNumSize()
{
	//配列の末尾を返したいので配列のサイズの最大値からfor文を回す
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//通った場所が保存されているかどうか見つける
		if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
			//何番目かを返す
			return PassedPlayerIndex;
		}
		else {
			return -1;
		}
	}
}

void CCheckPointManager::SetPassedPlayerNum(int iNum)
{
	//サイズ上限を超えたら先頭要素を削除
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//要素のない場所を見つける
		if (m_iPassedPlayerNum[PassedPlayerIndex] == -1)
		{
			//要素をいれる
			m_iPassedPlayerNum[PassedPlayerIndex] = iNum;
			return;
		}
	}
	//すべての要素が埋まっていたら
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//すべて初期化する
		memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));
	}

}

void CCheckPointManager::ClearPassedPlayerNum()
{
	//全要素を初期化
	memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));
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