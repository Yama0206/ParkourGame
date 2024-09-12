#include "Object.h"

//��`


void CObject::Init()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));			//���W
	memset(&m_vRot, 0.0f, sizeof(VECTOR));			//��]�l
	memset(&m_vScale, 0.0f, sizeof(VECTOR));		//�g�k��
	memset(&m_vSize, 0.0f, sizeof(VECTOR));			//�c�@���@���s���̃T�C�Y
	memset(&m_iHndl, -1, sizeof(int));				//�摜�n���h��
	memset(&m_IsAllive, true, sizeof(bool));		//�����t���O
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
	m_vScale = vScale;
}