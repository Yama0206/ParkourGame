#include "ItemBase.h"

void CItemBase::Load(int iModelHndl)
{
	//�����t���O��OFF�̎��͒��̏��������Ȃ�
	if (!m_IsAllive) return;

	//�����ǂݍ��ނ悤��MV1DuplicateModel���g��
	m_iHndl = MV1DuplicateModel(iModelHndl);
}


void CItemBase::Draw()
{
	//�����t���O��OFF�̎�
	if (!m_IsAllive) return;

	MV1DrawModel(m_iHndl);

}

//���̐ݒ�
void CItemBase::SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vScale = vScale;
}

void CItemBase::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}