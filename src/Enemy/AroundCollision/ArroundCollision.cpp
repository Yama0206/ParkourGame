#include "AroundCollision.h"

//’è‹`
constexpr float ADDRIGHT = 10.0f;

void CAroundCollision::Init()
{
	memset(&m_sSphere->m_vPos, 0.0f, sizeof(SSphere));
	memset(&m_sSphere->m_fRad, 0.0f, sizeof(SSphere));
}

void CAroundCollision::Update()
{

}

void CAroundCollision::ReflectCollision()
{

}