#include "Coin.h"

void CCoin::Step()
{
	//生存フラグがOFFのときは中の処理をしない
	if (!m_IsAllive) return;



}

void CCoin::SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale, VECTOR vSize, eType eType,int IsAllive)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vScale = vScale;
	m_vSize = vSize;
	m_eType = eType;

	m_IsAllive = IsAllive;
}