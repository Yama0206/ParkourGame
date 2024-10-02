#include "CheckPoint.h"

//’è‹`
static const float CHECKPOINT_X_SIZE = 100;
static const float CHECKPOINT_Y_SIZE = 100;
static const float CHECKPOINT_Z_SIZE = 100;

CCheckPoint::CCheckPoint()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vSize, 0.0f, sizeof(VECTOR));

	m_PlayerHit = false;
	m_fRad = 0.0f;
}

CCheckPoint::~CCheckPoint()
{

}

void CCheckPoint::SetInfo(VECTOR vPos, VECTOR vSize, float fRad)
{
	m_vPos = vPos;
	m_vSize = vSize;
	m_fRad = fRad;
}