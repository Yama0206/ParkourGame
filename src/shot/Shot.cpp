#include "Shot.h"

//��`
const float RADIUS = 1.0f;				//���a

//�R���X�g���N�^
CShot::CShot()
{
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_bIsActive = false;
}

//�f�X�g���N�^
CShot::~CShot()
{
	//�{���͕K�v�Ȃ����ǔO�̂���
	Fin();
}

//������
void CShot::Init()
{
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_fRadius = RADIUS;
	m_bIsActive = false;
}

void CShot::Fin()
{
	//���f���n���h�����
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//�f�[�^���[�h
void CShot::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
	}
}

void CShot::Draw()
{
	if (m_bIsActive)
	{
		MV1DrawModel(m_iHndl);
	}
}

void CShot::Step()
{
	if (!m_bIsActive) return;

	//���W�ɑ��x�����Z
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//���͈͂𒴂��������
	float fLength = 3000.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength)
	{
		m_bIsActive = false;
	}

	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
}

//���N�G�X�g
bool CShot::RequestShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//���łɔ��˂���Ă���
	if (m_bIsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bIsActive = true;

	return true;
}

//�����蔻���̏���
void CShot::HitCalc()
{
	//�Ƃ肠�����t���O����������
	m_bIsActive = false;
}

