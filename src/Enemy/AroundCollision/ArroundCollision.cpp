#include "AroundCollision.h"

//��`
constexpr float ADD_ARPUND_POS = 10.0f;			//���͂ɂ��铖���蔻��̍��W�̉��Z��

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