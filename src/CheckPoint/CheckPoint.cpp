#include "CheckPoint.h"

//’è‹`
static const float CHECKPOINT_X_SIZE = 100;
static const float CHECKPOINT_Y_SIZE = 100;
static const float CHECKPOINT_Z_SIZE = 100;

CCheckPoint::CCheckPoint()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vSize, 0.0f, sizeof(VECTOR));
	memset(m_NextCurrentNum, 0, sizeof(m_NextCurrentNum));

	m_iCurrentNum = -1;
	m_EnemyLastPassedNum = -1;
	m_IsArrived = false;
	m_IsPassedPlayer = false;
	m_iArrayIndex = 0;
	m_fRad = 0.0f;
}

CCheckPoint::~CCheckPoint()
{

}


void CCheckPoint::SetInfo(int Num, VECTOR vPos, float fRad, int* NextCPNum)
{
	m_vPos = vPos;
	m_fRad = fRad;
	m_iCurrentNum = Num;
	m_NextCurrentNum[0] = NextCPNum[0];
	m_NextCurrentNum[1] = NextCPNum[1];
	m_NextCurrentNum[2] = NextCPNum[2];
	m_NextCurrentNum[3] = NextCPNum[3];
}