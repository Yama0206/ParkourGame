#include "Object.h"

//��`


void CObject::Init()
{
	
}

void CObject::Load(int iMdHndl)
{
	if (m_iHndl == -1) {
		m_iHndl = MV1DuplicateModel(iMdHndl);
	}
}

void CObject::Step() 
{
	//�����t���O��OFF�̎����̏��������Ȃ�
	if (!m_IsAllive) return;



}

void CObject::Draw()
{
	//�����t���O��OFF�̎����̏��������Ȃ�
	if (!m_IsAllive) return;

	//�`�揈��
	MV1DrawModel(m_iHndl);

}

void CObject::Update()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1SetPosition(m_iHndl, m_vPos);
}

//���̐ݒ�
void CObject::SetInfo(VECTOR vPos, VECTOR vScale, VECTOR vRot)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSize = vScale;
}