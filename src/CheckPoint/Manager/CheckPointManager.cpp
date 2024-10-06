#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

//��`
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

	//���f���𕡐�
	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
			//��������N���X�̃|�C���^�ϐ����쐬
		CCheckPoint* cCheckPoint = new CCheckPoint();

			//��ō�����N���X�ɏ������
		cCheckPoint->SetInfo(m_cFileDataList.checkPointList[CheckPointIndex].m_iCPNum,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].m_vPos,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_vSize,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad);

			//�A�C�e���̃��X�g��push_back����
		m_cCheckPointList.push_back(cCheckPoint);
	}
}

CCheckPointManager* CCheckPointManager::GetInstance()
{
	//�܂���������Ă��Ȃ��Ȃ�
	if (m_Instance == NULL)
	{
		m_Instance = new CCheckPointManager();
	}

	return m_Instance;

}


//int CCheckPointManager::GetiCPNum(int iID)
//{
//	//�`�F�b�N�|�C���g�̐���for������
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//�`�F�b�N�|�C���g�̔ԍ��ƈ����̔ԍ�����v������
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//��v�����ԍ��̍��W��Ԃ�
//			return m_cCheckPointList[CheckPointIndex]->GetiCPNum();
//		}
//	}
//}

//VECTOR CCheckPointManager::GetPosVec(int iID)
//{
//	//�`�F�b�N�|�C���g�̐���for������
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//�`�F�b�N�|�C���g�̔ԍ��ƈ����̔ԍ�����v������
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//��v�����ԍ��̍��W��Ԃ�
//			return m_cCheckPointList[CheckPointIndex]->GetPosVec();
//		}
//	}
//}
//
//float CCheckPointManager::GetfRad(int iID)
//{
//	//�`�F�b�N�|�C���g�̐���for������
//	for (int CheckPointIndex = 0; CheckPointIndex < m_cFileDataList.checkPointList.size(); CheckPointIndex++) {
//		//�`�F�b�N�|�C���g�̔ԍ��ƈ����̔ԍ�����v������
//		if (m_cCheckPointList[CheckPointIndex]->GetiCPNum() == iID)
//		{
//			//��v�����ԍ��̍��W��Ԃ�
//			return m_cCheckPointList[CheckPointIndex]->GetRad();
//		}
//	}
//}

void CCheckPointManager::DeleteInstance()
{
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
	}
}