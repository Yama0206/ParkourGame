#include "ItemBase.h"

//���̐ݒ�
void CItemBase::SetInfo(VECTOR vPos, VECTOR vScale, VECTOR vRot)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vScale = vScale;
}