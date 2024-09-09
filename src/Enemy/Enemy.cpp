#include "Enemy.h"
#include <math.h>

//�R���X�g���N�^
CEnemy::CEnemy()
{
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_bIsActive = false;

	FrameCnt = 0;
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{
	//�{���͕K�v�Ȃ����ǔO�̂���
	Fin();
}

//������
void CEnemy::Init()
{
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_fRadius = RADIUS;
	m_bIsActive = false;
}

void CEnemy::Fin()
{
	//���f���n���h�����
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//�f�[�^���[�h
void CEnemy::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
		MV1SetScale(m_iHndl, VGet(5.0f, 5.0f, 5.0f));
	}
}

void CEnemy::Draw()
{
	if (m_bIsActive)
	{
		MV1DrawModel(m_iHndl);
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step()
{
	if (!m_bIsActive) return;

	//���W�ɑ��x�����Z
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//���͈͂𒴂��������
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_bIsActive = false;
	}

	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
}

//���N�G�X�g
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//���łɕ`�悳��Ă���
	if (m_bIsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bIsActive = true;

	//1�x���W�X�V�����Ă���
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//�����蔻���̏���
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//�Ƃ肠�����t���O����������
	m_bIsActive = false;
}

//���̐ݒ�
