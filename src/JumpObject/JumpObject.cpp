#include "../JumpObject/JumpObject.h"

constexpr VECTOR JUMPOBJECT_SIZE = { 30.0f,30.0f,30.0f };
constexpr VECTOR KARI_POS = { 5.0f,0.0f,150.0f };

//èâä˙ê›íË
void CJumpObject::InitValue()
{
	Init();

	m_vSize = JUMPOBJECT_SIZE;
	m_IsHit = false;

	m_vPos = KARI_POS;

	m_IsAllive = true;
}



