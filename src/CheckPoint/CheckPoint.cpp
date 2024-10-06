#include "CheckPoint.h"

//’è‹`
static const float CHECKPOINT_X_SIZE = 100;
static const float CHECKPOINT_Y_SIZE = 100;
static const float CHECKPOINT_Z_SIZE = 100;

CCheckPoint::CCheckPoint()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vSize, 0.0f, sizeof(VECTOR));

	m_eCP_Num = Point_1;
	m_iCPNum = 1;
	m_IsArrived = false;
	m_PlayerHit = false;
	m_fRad = 0.0f;
}

CCheckPoint::~CCheckPoint()
{

}

void CCheckPoint::AddCPNum()
{
	m_iCPNum++;
}

void CCheckPoint::SetInfo(int Num, VECTOR vPos, VECTOR vSize, float fRad)
{
	m_vPos = vPos;
	m_vSize = vSize;
	m_fRad = fRad;
	m_iCPNum = Num;

}