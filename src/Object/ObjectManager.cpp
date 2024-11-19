#include "ObjectManager.h"

//定義
const char OBJECT_MODEL_PATH[] = {""};

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::Init()
{
	for (int ObjectIndex = 0; ObjectIndex<OBJECT_NUM; ObjectIndex++)
	{
		m_cObject[ObjectIndex].Init();
	}
	
}

void CObjectManager::InitValue()
{
	
}

void CObjectManager::Load()
{
	m_cObjectRead.ReadFile();

	//オリジナルモデルの読み込み
	//種類別にモデルを読み込んでおく
	int iHndl = MV1LoadModel(OBJECT_MODEL_PATH);

	//モデルを複製
	for (int ObjectIndex = 0; ObjectIndex < m_cObjectRead.objectInfoList.size(); ObjectIndex++) {
		switch (m_cObjectRead.objectInfoList[ObjectIndex].m_eType) {
		case a:
			//aタイプの敵に情報を設定
			/*m_cObject[ObjectIndex].SetInfo(m_cObjectRead.objectInfoList[ObjectIndex].m_vPos,
				m_cObjectRead.objectInfoList[ObjectIndex].m_vSize,
				m_cObjectRead.objectInfoList[ObjectIndex].m_vRot);*/


			break;
		case b:

			break;
		case c:

			break;
		case d:

			break;
		default:
			break;
		}
	}
}

void CObjectManager::Step()
{

}

void CObjectManager::Draw()
{

}

void CObjectManager::Fin()
{

}

void CObjectManager::Update()
{
	for (int ObjectIndex = 0; ObjectIndex < OBJECT_NUM; ObjectIndex++) {
		m_cObject[ObjectIndex].Update();
	}
}