#include "ParkourObjectManager.h"

CParkourObjectManager* CParkourObjectManager::m_Instance = NULL;

CParkourObjectManager* CParkourObjectManager::GetInstance()
{
	//まだ生成されていないなら
	if (m_Instance == NULL)
	{
		m_Instance = new CParkourObjectManager();
	}

	return m_Instance;

}

void CParkourObjectManager::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}

CParkourObjectManager::CParkourObjectManager()
{

}

CParkourObjectManager::~CParkourObjectManager()
{
	for (int ParkourObjectIndex = 0; ParkourObjectIndex < m_cParkourObjectList.size(); ParkourObjectIndex++)
	{
		delete m_cParkourObjectList[ParkourObjectIndex];
	}
}

void CParkourObjectManager::Init()
{

}

void CParkourObjectManager::Load()
{
	m_cFileDataList.ReadFile();

	//モデルを複製
	for (int ParkourObjectIndex = 0; ParkourObjectIndex < m_cFileDataList.sparkourObjectInfoList.size(); ParkourObjectIndex++) {
		switch (m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_eType) {
		case FENCE:
			//情報を入れるクラスのポインタ変数を作成
			CFence* cFence = new CFence();
			//上で作ったクラスに情報を入力
			cFence->SetInfo(m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vObjectPos, 
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vFrontPos, m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vBackPos, 
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vRightPos, m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vLeftPos,
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_IsAllive);

			//フェンスモデルの読み込み

			//アイテムのリストにpush_backする
			m_cParkourObjectList.push_back(cFence);

		break;

		case 1:

		break;

		case 2:

		break;
		}
	}
}

void CParkourObjectManager::Update()
{
	for (int ParkourObjectIndex = 0; ParkourObjectIndex < m_cParkourObjectList.size(); ParkourObjectIndex++)
	{
		m_cParkourObjectList[ParkourObjectIndex]->Update();
	}
}

void CParkourObjectManager::Draw()
{
	for (int ParkourObjectIndex = 0; ParkourObjectIndex < m_cParkourObjectList.size(); ParkourObjectIndex++)
	{
		m_cParkourObjectList[ParkourObjectIndex]->Update();
	}
}