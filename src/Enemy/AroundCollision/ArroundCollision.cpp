#include "AroundCollision.h"

//’è‹`
constexpr float ADD_ARPUND_POS = 10.0f;			//ŽüˆÍ‚É‚Â‚¯‚é“–‚½‚è”»’è‚ÌÀ•W‚Ì‰ÁŽZ—Ê

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