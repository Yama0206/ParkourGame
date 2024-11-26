#include "CheckPoint.h"

//’è‹`
static const float CHECKPOINT_X_SIZE = 75;
static const float CHECKPOINT_Y_SIZE = 1;
static const float CHECKPOINT_Z_SIZE = 75;

CCheckPoint::CCheckPoint()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(m_NextCurrentNum, 0, sizeof(m_NextCurrentNum));

	m_vSize = VGet(CHECKPOINT_X_SIZE, CHECKPOINT_Y_SIZE, CHECKPOINT_Z_SIZE);

	m_iCurrentNum = -1;
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