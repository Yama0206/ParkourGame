#include "CheckPointManager.h"

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
		cCheckPoint->SetInfo(m_cFileDataList.checkPointList[CheckPointIndex].m_vPos,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_vSize,
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad);

			//�A�C�e���̃��X�g��push_back����
		m_cCheckPointList.push_back(cCheckPoint);
	}
}