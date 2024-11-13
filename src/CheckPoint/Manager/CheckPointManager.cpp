#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

//��`
const int CHECKPOINT_NUM = 10;
constexpr int PLAYER_PASSED_LIST_SIZE = 20;				//�v���C���[���ʂ����ꏊ��ۑ����Ă������X�g�̃T�C�Y

CCheckPointManager::CCheckPointManager()
{
		//�v���C���[���ʂ����ꏊ
	m_iLastPassedEnemyNum = 0;									//�G���Ō�ɒʂ����ꏊ
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

void CCheckPointManager::Step()
{
	CDebugManager::GetInstance()->AddFormatString(400, 0, "�G���Ō�ɒʂ����ꏊ = %d", m_iLastPassedEnemyNum);
	CDebugManager::GetInstance()->AddFormatString(0, 200, "�v���C���[���ʂ����ꏊ���i�[���Ă��郊�X�g�T�C�Y = %d", CHECKPOINT_INDEX);
	for (int i = 0; i < CHECKPOINT_INDEX; i++) {
		CDebugManager::GetInstance()->AddFormatString(0, 220+(i*20), "�v���C���[���ʂ����ꏊ = %d", m_iPassedPlayerNum[i]);
	}
}

int CCheckPointManager::GetPassedPlayerNum()
{
	//�ʂ����ꏊ��1�ȏ゠���
	for (int PassedPlayerIndex = PLAYER_PASSED_LIST_SIZE - 1; PassedPlayerIndex >= 0; PassedPlayerIndex++)
	{
		//�����̒l��Ԃ�
		if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
			return m_iPassedPlayerNum[PassedPlayerIndex];
		}
		else {
			//�����Ȃ����-1��Ԃ�
			return -1;
		}
	}
}

void CCheckPointManager::SetPassedPlayerNum(int Num)
{
	//�T�C�Y����𒴂�����擪�v�f���폜
	if (CHECKPOINT_INDEX > PLAYER_PASSED_LIST_SIZE){
		for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
		{

			if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
				m_iPassedPlayerNum[PassedPlayerIndex] = -1;
				break;
			}
		}
	}
	//
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//�v�f�̂Ȃ��ꏊ��������
		if (m_iPassedPlayerNum[PassedPlayerIndex] == -1)
		{
			m_iPassedPlayerNum[PassedPlayerIndex] = Num;
		}
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

void CCheckPointManager::DeleteInstance()
{
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
	}
}