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
	for (int ItemIndex = 0; ItemIndex < m_cFileDataList.sparkourObjectInfoList.size(); ItemIndex++) {
		switch (m_cFileDataList.sparkourObjectInfoList[ItemIndex].m_eType) {
		case TYPE_1:
			//情報を入れるクラスのポインタ変数を作成

			//上で作ったクラスに情報を入力

			//アイテムのリストにpush_backする

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