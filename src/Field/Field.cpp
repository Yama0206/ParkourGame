#include "Field.h"

//������
void CField::Init()
{
	m_vPos = VGet(0.0f, -50.0f, 0.0f);
	m_vScale = { FIELD_X_SCALE, FIELD_Y_SCALE, FIELD_Z_SCALE };
	m_vSize = { FIELD_X_SIZE, FIELD_Y_SIZE, FIELD_Z_SIZE };

	m_iHndl = -1;						//�摜�n���h��
}

//�ǂݍ���
void CField::Load()
{
	m_iHndl = MV1LoadModel(FIELD_PATH);

	//�R���W�������\�z
	MV1SetupCollInfo(m_iHndl);

}

//�ʏ폈��
void CField::Step() {}

//�`�揈��
void CField::Draw()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1DrawModel(m_iHndl);
}

//�X�V����
VECTOR CField::HitCheck(VECTOR vCenter, float fRadius)
{
	VECTOR vOut = { 0.0f, 0.0f, 0.0f };			//���̂��w�i�ɂ߂荞�񂾋���
	m_IsHitFrag = false;

	MV1_COLL_RESULT_POLY_DIM res;		//�����蔻�茋�ʊi�[�\����
	res = MV1CollCheck_Sphere(m_iHndl, -1, vCenter, fRadius);

	//�q�b�g���Ă���΃t���O��true��
	for (int FieldIndex = 0; FieldIndex < res.HitNum; FieldIndex++)
	{
		//���̒��S�ƍŋߓ_�̍��W�̍ŒZ�������v�Z
		VECTOR vSub = VSub(res.Dim[FieldIndex].HitPosition, vCenter);
		//�߂荞�񂾋������v�Z
		float len = VSize(vSub);
		//���a-���S�ƍŋߓ_�̍��W�̍ŒZ����
		len = fRadius - len;
		//�@���x�N�g�����v�Z����
		VECTOR vAns = VScale(res.Dim[FieldIndex].Normal, len);
		//�߂荞�ݗʂ����Z
		vOut = VAdd(vOut, vAns);

		m_IsHitFrag = true;
	}
	MV1CollResultPolyDimTerminate(res);

	return vOut;
}

void CField::UpDate()
{
	MV1SetPosition(m_iHndl, m_vPos);
}

//�I������
void CField::Fin()
{
	if (m_iHndl != -1)
	{
		MV1TerminateCollInfo(m_iHndl);		//�R���W�������j��
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}
