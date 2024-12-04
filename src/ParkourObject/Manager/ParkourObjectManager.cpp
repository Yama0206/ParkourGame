#include "ParkourObjectManager.h"

CParkourObjectManager* CParkourObjectManager::m_Instance = NULL;

CParkourObjectManager* CParkourObjectManager::GetInstance()
{
	//�܂���������Ă��Ȃ��Ȃ�
	if (m_Instance == NULL)
	{
		m_Instance = new CParkourObjectManager();
	}

	return m_Instance;

}

void CParkourObjectManager::DeleteInstance()
{
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
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

	//���f���𕡐�
	for (int ParkourObjectIndex = 0; ParkourObjectIndex < m_cFileDataList.sparkourObjectInfoList.size(); ParkourObjectIndex++) {
		switch (m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_eType) {
		case FENCE:
			//��������N���X�̃|�C���^�ϐ����쐬
			CFence* cFence = new CFence();
			//��ō�����N���X�ɏ������
			cFence->SetInfo(m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vObjectPos, 
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vFrontPos, m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vBackPos, 
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vRightPos, m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_vLeftPos,
				m_cFileDataList.sparkourObjectInfoList[ParkourObjectIndex].m_IsAllive);

			//�t�F���X���f���̓ǂݍ���

			//�A�C�e���̃��X�g��push_back����
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