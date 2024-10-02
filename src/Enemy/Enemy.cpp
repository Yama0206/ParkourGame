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
	m_IsActive = false;

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
	m_IsActive = false;
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
	if (m_IsActive)
	{
		MV1DrawModel(m_iHndl);
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step(VECTOR vPlayerPos, VECTOR vPos, int Index)
{
	//�G�̐����t���O��OFF�̎����̏������s��Ȃ�
	if (!m_IsActive) return;
	
	//�v���C���[��ǂ�������
	TrackingPlayer(vPlayerPos);

	//�`�F�b�N�|�C���g�Ɍ�����
	//MoveCheckPoint(vPos, Index);

}

//�v���C���[��ǐՂ���
void CEnemy::TrackingPlayer(VECTOR vPlayerPos)
{
	//�z�[�~���O����
	VECTOR PlayerVec;
	//�G����v���C���[�Ɍ������x�N�g��
	PlayerVec.x = vPlayerPos.x - m_vPos.x;
	PlayerVec.y = 0.0f;
	PlayerVec.z = vPlayerPos.z - m_vPos.z;

	float fCrossZ = 0.0f;

	//���݂̐i�s�����̃x�N�g��
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_vRot.y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_vRot.y) * -1.0f;

	//2�̃x�N�g���̊O�ς��v�Z
	fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

	//fCrossZ�̌v�Z���ʂō��E�̔�����s��
	if (fCrossZ > 0)
	{
		m_vRot.y += 0.1;
	}
	else if (fCrossZ < 0)
	{
		m_vRot.y -= 0.1;
	}

	m_vPos.x += sinf(m_vRot.y) * -0.3f;
	m_vPos.z += cosf(m_vRot.y) * -0.3f;

}

void CEnemy::TrackingCheckPoint()
{
	for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetCheckPointSize(); CheckPointIndex++) {
		//�z�[�~���O����
		VECTOR PlayerVec;
	
		//�G����v���C���[�Ɍ������x�N�g��
		PlayerVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x;
		PlayerVec.y = 0.0f;
		PlayerVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z;
		

		float fCrossZ = 0.0f;

		//���݂̐i�s�����̃x�N�g��
		VECTOR  MoveVec;

		memset(&MoveVec, 0.0f, sizeof(MoveVec));

		MoveVec.x = sinf(m_vRot.y) * -1.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = cosf(m_vRot.y) * -1.0f;

		//2�̃x�N�g���̊O�ς��v�Z
		fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

		//fCrossZ�̌v�Z���ʂō��E�̔�����s��
		if (fCrossZ > 0)
		{
			m_vRot.y += 0.1;
		}
		else if (fCrossZ < 0)
		{
			m_vRot.y -= 0.1;
		}

		m_vPos.x += sinf(m_vRot.y) * -0.3f;
		m_vPos.z += cosf(m_vRot.y) * -0.3f;
	}
}

//���N�G�X�g
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//���łɕ`�悳��Ă���
	if (m_IsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_IsActive = true;

	//1�x���W�X�V�����Ă���
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

void CEnemy::Update()
{
	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
}

//�����蔻���̏���
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//�Ƃ肠�����t���O����������
	m_IsActive = false;
}

//���̐ݒ�
void CEnemy::SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vScale, VECTOR vRot, bool IsActive)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSpeed = vSpeed;
	m_vSize = vScale;
	m_IsActive = IsActive;
}