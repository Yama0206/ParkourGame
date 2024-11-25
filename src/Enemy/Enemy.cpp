#include "Enemy.h"
#include <math.h>

//��`
constexpr int ENEMY_CP_MAX = 4;						//�`�F�b�N�|�C���g�̐�
constexpr int ENEMY_SEARCH_AREA = 200;				//�G���v���C���[�����G����͈�
constexpr int ENEMY_TRACKING_AREA = 300;			//�G���v���C���[��ǂ�������͈�
constexpr int ENEMY_TRACKING_PALYER_AREA = 50;		//�G���v���C���[�𒼐ڒǂ�������

//�R���X�g���N�^
CEnemy::CEnemy()
{
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSize, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));

	m_iHndl = -1;
	m_IsAllive = false;
	m_iNextCheckPointNum = 0;
	m_iLastPassedCP = -1;
	m_fRad = 5;
	m_fTrackingRad = ENEMY_TRACKING_AREA;
	m_fSearchRad = ENEMY_SEARCH_AREA;
	m_fTrackingPlayerRad = ENEMY_TRACKING_PALYER_AREA;
	m_eState = Patrol;
	m_eOldState = Patrol;

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
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSize, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));

	m_iHndl = -1;
	m_IsAllive = false;
	m_iNextCheckPointNum = 0;
	m_iLastPassedCP = -1;
	m_fRad = 5;
	m_fTrackingRad = ENEMY_TRACKING_AREA;
	m_fSearchRad = ENEMY_SEARCH_AREA;
	m_fTrackingPlayerRad = ENEMY_TRACKING_PALYER_AREA;
	m_eState = Patrol;
	m_eOldState = Patrol;

	FrameCnt = 0;
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
		MV1SetScale(m_iHndl, m_vScale);
	}
}

void CEnemy::Draw()
{
	if (m_IsAllive)
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
	CDebugManager::GetInstance()->AddFormatString(0,0,"�G�̍��W = %f,%f,%f", m_vPos.x, m_vPos.y,m_vPos.z);
	CDebugManager::GetInstance()->AddFormatString(0,20,"���̏�� = %d",m_eState);
	CDebugManager::GetInstance()->AddFormatString(0,40,"1F�O�̏�� = %d",m_eOldState);
	CDebugManager::GetInstance()->AddFormatString(0, 60, "���Ɍ������`�F�b�N�|�C���g�̔ԍ� = %d", m_iNextCheckPointNum);
	CDebugManager::GetInstance()->AddFormatString(0, 80, "�Ō�ɒʂ����`�F�b�N�|�C���g�̔ԍ� = %d",m_iLastPassedCP);
	CDebugManager::GetInstance()->AddFormatString(0, 100, "���G�͈� = %f", m_fSearchRad);
	CDebugManager::GetInstance()->AddFormatString(0, 120, "�v���C���[�ǐՔ͈� = %f", m_fTrackingPlayerRad);


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

	m_vPos.x += sinf(m_vRot.y) * -m_vSpeed.x;
	m_vPos.z += cosf(m_vRot.y) * -m_vSpeed.z;

}

void CEnemy::TrackingCheckPoint(int CheckPointIndex)
{
	//�z�[�~���O����
	VECTOR CheckPosVec;
	//�G����`�F�b�N�|�C���g�������x�N�g��
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - m_vPos.x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z - m_vPos.z;

	float fCrossZ = 0.0f;

	//���݂̐i�s�����̃x�N�g��
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_vRot.y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_vRot.y) * -1.0f;

	//2�̃x�N�g���̊O�ς��v�Z
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZ�̌v�Z���ʂō��E�̔�����s��
	if (fCrossZ > 0)
	{
		m_vRot.y += 0.1;
	}
	else if (fCrossZ < 0)
	{
		m_vRot.y -= 0.1;
	}

	m_vPos.x += sinf(m_vRot.y) * - m_vSpeed.x;
	m_vPos.z += cosf(m_vRot.y) * - m_vSpeed.z;
}

void CEnemy::NearCheckPointFind()
{
	float fTwoPoint_1, fTwoPoint_2;

	fTwoPoint_1 = -1.0f;
	fTwoPoint_2 = -1.0f;

	for (int i = 0; i < CCheckPointManager::GetInstance()->GetSize(); i++) {

		//�l�����������ĂȂ�������
		if (fTwoPoint_1 == -1.0f)
		{
			//�G���W�ƃ`�F�b�N�|�C���g���W����������Βl��ϐ��Ɋi�[
			fTwoPoint_1 = fabsf(VecTwoPoint3D(m_vPos, CCheckPointManager::GetInstance()->GetPosVec(i)));
			m_iNextCheckPointNum = i;
			continue;
		}


		//�G���W�ƃ`�F�b�N�|�C���g���W����������Βl��ϐ��Ɋi�[
		fTwoPoint_2 = fabsf(VecTwoPoint3D(m_vPos, CCheckPointManager::GetInstance()->GetPosVec(i)));


		//2�ڂ̕ϐ��̂ق���������������
		if (fTwoPoint_1 > fTwoPoint_2)
		{
			fTwoPoint_1 = fTwoPoint_2;
			m_iNextCheckPointNum = i;
		}
	}
}

//���N�G�X�g
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//���łɕ`�悳��Ă���
	if (m_IsAllive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_IsAllive = true;

	//1�x���W�X�V�����Ă���
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

void CEnemy::Update()
{
	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}

//�����蔻���̏���
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//�Ƃ肠�����t���O����������
	m_IsAllive = false;
}

//���̐ݒ�
void CEnemy::SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vScale, VECTOR vRot, bool IsFrag)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSpeed = vSpeed;
	m_vScale = vScale;
	m_IsAllive = IsFrag;
}

void CEnemy::ReflectCollision(VECTOR vAddVec)
{
	//�I�[���[���Ȃ牽�����Ȃ�
	if (vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;

	m_vPos = VAdd(vAddVec, m_vPos);

	MV1SetPosition(m_iHndl, m_vPos);

	//�����������͏d�͏��������Ȃ�
}