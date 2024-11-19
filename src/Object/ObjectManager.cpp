#include "ObjectManager.h"

//��`
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

	//�I���W�i�����f���̓ǂݍ���
	//��ޕʂɃ��f����ǂݍ���ł���
	int iHndl = MV1LoadModel(OBJECT_MODEL_PATH);

	//���f���𕡐�
	for (int ObjectIndex = 0; ObjectIndex < m_cObjectRead.objectInfoList.size(); ObjectIndex++) {
		switch (m_cObjectRead.objectInfoList[ObjectIndex].m_eType) {
		case a:
			//a�^�C�v�̓G�ɏ���ݒ�
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