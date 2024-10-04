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
	m_PlayerHit = false;
	m_fRad = 0.0f;
}

CCheckPoint::~CCheckPoint()
{

}

void CCheckPoint::AddCPNum()
{
	if (m_eCP_Num >= Point_1 && m_eCP_Num < Point_2) 
	{
		m_eCP_Num = Point_2;
	}
	//else if (m_eCP_Num < Point_3)
	//{
	//	m_eCP_Num = Point_3;
	//}
	//else if (m_eCP_Num < Point_4)
	//{
	//	m_eCP_Num = Point_4;
	//}
	//else if (m_eCP_Num < Point_5)
	//{
	//	m_eCP_Num = Point_5;
	//}
}

void CCheckPoint::SetInfo(eCP_Num Num, VECTOR vPos, VECTOR vSize, float fRad)
{
	m_vPos = vPos;
	m_vSize = vSize;
	m_fRad = fRad;
	m_eCP_Num = Num;

}