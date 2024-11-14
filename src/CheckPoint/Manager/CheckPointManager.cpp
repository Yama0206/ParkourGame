#include "CheckPointManager.h"

CCheckPointManager* CCheckPointManager::m_Instance = NULL;

//��`
const int CHECKPOINT_NUM = 10;

CCheckPointManager::CCheckPointManager()
{
	//�v���C���[���ʂ����ꏊ
	memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));

	//�v���C���[���Ō�ɒʂ����ꏊ
	m_iLastPassedPlayerNum = -1;
	//�G���Ō�ɒʂ����ꏊ
	m_iLastPassedEnemyNum = -1;
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
	CDebugManager::GetInstance()->AddFormatString(0, 200, "�v���C���[���ʂ����ꏊ���i�[���Ă��郊�X�g�T�C�Y = %d", PLAYER_PASSED_LIST_SIZE);
	for (int i = 0; i < PLAYER_PASSED_LIST_SIZE; i++) {
		CDebugManager::GetInstance()->AddFormatString(0, 220+(i*20), "�v���C���[���ʂ����ꏊ%d�Ԗ� = %d", i,m_iPassedPlayerNum[i]);
	}
	CDebugManager::GetInstance()->AddFormatString(500, 600, "�v���C���[���ʂ����ꏊ���i�[���Ă��郊�X�g�̍��̃T�C�Y = %d", CCheckPointManager::GetInstance()->GetPassedPlayerNumSize());
}

int CCheckPointManager::GetPassedPlayerNum()
{
	//�z��̖�����Ԃ������̂Ŕz��̃T�C�Y�̍ő�l����for������
	for (int PassedPlayerIndex = PLAYER_PASSED_LIST_SIZE - 1; PassedPlayerIndex >= 0; PassedPlayerIndex++)
	{
		//�ʂ����ꏊ���ۑ�����Ă��邩�ǂ���������
		if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
			//�����̒l��Ԃ�
			return m_iPassedPlayerNum[PassedPlayerIndex];
		}
		else {
			//�����Ȃ����-1��Ԃ�
			return -1;
		}
	}
}

int CCheckPointManager::GetPassedPlayerNumSize()
{
	//�z��̖�����Ԃ������̂Ŕz��̃T�C�Y�̍ő�l����for������
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//�ʂ����ꏊ���ۑ�����Ă��邩�ǂ���������
		if (m_iPassedPlayerNum[PassedPlayerIndex] != -1) {
			//���Ԗڂ���Ԃ�
			return PassedPlayerIndex;
		}
		else {
			return -1;
		}
	}
}

void CCheckPointManager::SetPassedPlayerNum(int iNum)
{
	//�T�C�Y����𒴂�����擪�v�f���폜
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//�v�f�̂Ȃ��ꏊ��������
		if (m_iPassedPlayerNum[PassedPlayerIndex] == -1)
		{
			//�v�f�������
			m_iPassedPlayerNum[PassedPlayerIndex] = iNum;
			return;
		}
	}
	//���ׂĂ̗v�f�����܂��Ă�����
	for (int PassedPlayerIndex = 0; PassedPlayerIndex < PLAYER_PASSED_LIST_SIZE; PassedPlayerIndex++)
	{
		//���ׂď���������
		memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));
	}

}

void CCheckPointManager::ClearPassedPlayerNum()
{
	//�S�v�f��������
	memset(m_iPassedPlayerNum, -1, sizeof(m_iPassedPlayerNum));
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