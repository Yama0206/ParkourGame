#include "ParkourObject.h"


void CParkourObject::Load(int iModelHndl)
{
	//�����t���O��OFF�̎��͒��̏��������Ȃ�
	if (!m_IsAllive) return;

	//�����ǂݍ��ނ悤��MV1DuplicateModel���g��
	m_iHndl = MV1DuplicateModel(iModelHndl);
}

void CParkourObject::SetInfo(VECTOR vPos, VECTOR vScale, bool IsFrag)
{
	m_vPos = vPos;
	m_vScale = vScale;
	m_IsAllive = IsFrag;
}

void CParkourObject::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}