#include "AroundCollision.h"

//定義
constexpr float ADD_ARPUND_POS = 10.0f;			//周囲につける当たり判定の座標の加算量

void CAroundCollision::Init()
{
	memset(&m_sSphere->m_vPos, 0.0f, sizeof(SSphere));
	memset(&m_sSphere->m_fRad, 0.0f, sizeof(SSphere));
}

void CAroundCollision::SetAroundCollisionInfo(VECTOR vCenterPos)
{
	//m_sSphere[RIGHT].m_vPos =	VAdd()
}

void CAroundCollision::ReflectCollision()
{

}