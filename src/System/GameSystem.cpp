#include "GameSystem.h"

CGameSystem* CGameSystem::m_Instance = NULL;

CGameSystem* CGameSystem::GetInstance()
{
	//�܂���������Ă��Ȃ��Ȃ�
	if (m_Instance == NULL)
	{
		m_Instance = new CGameSystem();
	}

	return m_Instance;

}

void CGameSystem::DeleteInstance()
{
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
	}
}

void CGameSystem::Load()
{

}

void CGameSystem::Draw()
{

}

void CGameSystem::CntFream()
{
	//60�t���[����������[���ɖ߂�
	if (m_iFreamCnt > 60) {
		m_iFreamCnt = 0;
	}

	//�t���[�����J�E���g����
	m_iFreamCnt++;
	
}

void CGameSystem::CntTime()
{
	//60�t���[����������1�b�J�E���g����
	if (m_iFreamCnt > 60) {
		m_iTimeCnt++;
	}
}

void CGameSystem::ClearDecision()
{
	
}