#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"
#include "../Math/Math.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include "../Debug/DebugManager.h"

//��`
constexpr float RADIUS = 5.0f;					//�G�̔��a
constexpr float ENEMY_HALF_HEIGHT = 10.0f;	//�G�̏c�T�C�Y�̔���

//�G�̏��
enum EnemyState
{
	Patrol = 1,				//����
	TrackingCheckPoint,		//�`�F�b�N�|�C���g��ǐ�
	TrackingPlayer,			//�v���C���[��ǐ�
};


class CEnemy
{
protected:
	VECTOR m_vPos;					//���W
	VECTOR m_vSpeed;				//�ړ����x
	VECTOR m_vRot;					//��]�l
	VECTOR m_vSize;					//�c�@���@���s���̃T�C�Y
	VECTOR m_vScale;				//�g�k��
	VECTOR m_vCenterPos;			//���S���W

	int		m_iHndl;				//���f���n���h��
	bool	m_IsAllive;				//�����t���O
	float	m_fRad;					//���a
	float	m_fTrackingRad;			//�ǐՂ��锼�a
	float	m_fTrackingPlayerRad;	//�v���C���[�𒼐ڒǐՂ���͈�
	float	m_fSearchRad;			//���G�͈�
	int		m_iNextCheckPointNum;	//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
	int		m_iLastPassedCP;		//�G���ʂ����`�F�b�N�|�C���g

	int FrameCnt;					//�t���[���J�E���g

	EnemyState m_eState;			//�G�̏��
	EnemyState m_eOldState;			//�G��1F�O�̏��

public:

	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemy();
	~CEnemy();

public:
	//������
	void Init();

	//�f�[�^���[�h
	void Load(int iMdlHndl);
	//�I������
	void Fin();
	//���t���[���Ăԏ���
	void Step();
	//�`�揈��
	void Draw();
	//�X�V����
	void Update();

	//vPos		:		�������W
	//vSpeed	:		�ړ����x(�����x�N�g����)
	//@return	:		true = ���N�G�X�g���� false = ���s
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

public:
	//�v���C���[��ǐ�
	void TrackingPlayer(VECTOR vPlayerPos);
	//�`�F�b�N�|�C���g
	void TrackingCheckPoint(int CheckPointIndex);

public:
	//���W�擾
	// �Q�Ɠn��
	// vPos		:	���W��ۑ�����ϐ�
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	
	//�擾�֐�
	VECTOR		GetPosVec()					{ return m_vPos; }													//���W
	void		GetCenterPos(VECTOR& vPos)	{ vPos = VAdd(m_vPos, VGet(0.0f, ENEMY_HALF_HEIGHT, 0.0f)); }		//���S���W
	VECTOR		GetSizeVec()				{ return m_vSize; }													//�傫��
	VECTOR		GetSpeedVec()				{ return m_vSpeed; }												//����
	VECTOR		GetRotVec()					{ return m_vRot; }													//��]�l
	int			GetNextCheckPointNum()		{ return m_iNextCheckPointNum; }									//���Ɍ������`�F�b�N�|�C���g
	float		GetRadius()					{ return m_fRad; }													//���a
	float		GetTrackingRad()			{ return m_fTrackingRad; }											//�ǐՂ����锼�a
	float		GetSearchRad()				{ return m_fSearchRad; }											//���G�����锼�a
	float		GetTrackingPlayerRad()		{ return m_fTrackingPlayerRad; }									//�v���C���[�𒼐ڒǂ�������͈�
	int			GetLastPassedCheckPoint()	{ return m_iLastPassedCP; }											//�Ō�ɒʂ����`�F�b�N�|�C���g�̔ԍ�
	EnemyState	GetState()					{ return m_eState; }												//���݂̏��
	EnemyState	GetOldState()				{ return m_eOldState; }												//1F�O�̏��

	//��������擾
	bool GetIsActiv() { return m_IsAllive; }

	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot, bool IsFrag);	

	//�ݒ�֐�
	void SetPosVec		(VECTOR vPos)				{ m_vPos = vPos; }				//���W
	void SetCenterPosVec(VECTOR vCenter)			{ m_vCenterPos = vCenter; }		//���S���W
	void SetSizeVec		(VECTOR vSize)				{ m_vSize = vSize; }			//�傫��
	void SetSpeedVec	(VECTOR vSpeed)				{ m_vSpeed = vSpeed; }			//����
	void SetRotVec		(VECTOR vRot)				{ m_vRot = vRot; }				//��]�l

	void SetPosVec_X(float fPos)	{ m_vPos.x = fPos; }			//X���W
	void SetPosVec_Y(float fPos)	{ m_vPos.y = fPos; }			//Y���W
	void SetPosVec_Z(float fPos)	{ m_vPos.z = fPos; }			//Z���W

	void SetRotVec_X(float fRot)	{ m_vRot.x = fRot; }			//X��]�l
	void SetRotVec_Y(float fRot)	{ m_vRot.y = fRot; }			//Y��]�l
	void SetRotVec_Z(float fRot)	{ m_vPos.z = fRot; }			//Z��]�l

	//�Ō�ɒʂ����`�F�b�N�|�C���g�̔ԍ�
	void SetLastPassedCheckPoint(int Num) { m_iLastPassedCP = Num; }
	//���Ɍ������`�F�b�N�|�C���g�̔ԍ���ݒ�
	void SetNextCheckPointNum(int Num) { m_iNextCheckPointNum = Num; }

	//���
	void SetState	(EnemyState eState)	{ m_eState = eState; }			//����
	void SetOldState(EnemyState eState) { m_eOldState = eState; }		//1F�O

	//�����蔻���̏���
	void HitCalc();
	
	//�ʂ����`�F�b�N�|�C���g�̏�����
	void ClearLastPassedCheckPoint() { m_iLastPassedCP = -1; }
	void ClearNextPassedCheckPoint() { m_iNextCheckPointNum = -1; }

	//��ԋ߂��̃`�F�b�N�|�C���g��T��
	void NearCheckPointFind();

	//
	void ReflectCollision(VECTOR vAddVec);
};


