#include "GameSystem.h"

CGameSystem* CGameSystem::m_Instance = NULL;

CGameSystem* CGameSystem::GetInstance()
{
	//まだ生成されていないなら
	if (m_Instance == NULL)
	{
		m_Instance = new CGameSystem();
	}

	return m_Instance;

}

void CGameSystem::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
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
	//60フレームたったらゼロに戻す
	if (m_iFreamCnt > 60) {
		m_iFreamCnt = 0;
	}

	//フレームをカウントする
	m_iFreamCnt++;
	
}

void CGameSystem::CntTime()
{
	//60フレームたったら1秒カウントする
	if (m_iFreamCnt > 60) {
		m_iTimeCnt++;
	}
}

void CGameSystem::ClearDecision()
{
	
}