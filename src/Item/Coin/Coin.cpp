#include "Coin.h"

void CCoin::Step()
{
	//�����t���O��OFF�̂Ƃ��͒��̏��������Ȃ�
	if (!m_IsAllive) return;



}

void CCoin::SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale, int IsAllive)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vScale = vScale;

	m_IsAllive = IsAllive;
}