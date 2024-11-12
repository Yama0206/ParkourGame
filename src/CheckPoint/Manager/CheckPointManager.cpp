#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

//��`
const int CHECKPOINT_NUM = 10;
constexpr int PLAYER_PASSED_LIST_SIZE = 20;				//�v���C���[���ʂ����ꏊ��ۑ����Ă������X�g�̃T�C�Y

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
						  	 m_cFileDataList.checkPointList[CheckPointIndex].fRad,
							 m_cFileDataList.checkPointList[CheckPointIndex].m_NextCPNum);
		
		//�z��̐���for������
		for (int ArrayIndex = 0; ArrayIndex < NEXT_CHECKPOINT_NUM; ArrayIndex++)
		{
			//���Ɍ������ꏊ��-1�ȊO�������玟�Ɍ}����ꏊ�̐���+1����
			if (m_cFileDataList.checkPointList[CheckPointIndex].m_NextCPNum[ArrayIndex] != -1)
			{
				cCheckPoint->AddArayIndex();
			}
		}

			//�A�C�e���̃��X�g��push_back����
		m_cCheckPointList.push_back(cCheckPoint);
	}
}

int CCheckPointManager::GetPassedPlayerNum()
{
	//�ʂ����ꏊ��1�ȏ゠���
	if (m_iPassedPlayerNum.size() > 0){
		//�����̒l��Ԃ�
		return m_iPassedPlayerNum.back();
	}
	else {
		//�����Ȃ����-1��Ԃ�
		return -1;
	}
	 
}

void CCheckPointManager::SetPassedPlayerNum(int Num)
{
	//�T�C�Y����𒴂�����擪�v�f���폜
	if (m_iPassedPlayerNum.size() > PLAYER_PASSED_LIST_SIZE) {
		m_iPassedPlayerNum.erase(m_iPassedPlayerNum.begin());
	}
	//�l������
	m_iPassedPlayerNum.push_back(Num);
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

void CCheckPointManager::DeleteInstance()
{
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
	}
}