#pragma once

#include "Dxlib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../shot/ShotManager.h"
#include "../Model/Model.h"
#include "../Math/Math.h"
#include "../Input/Pad/Pad.h"
#include "../Camera/CameraManager.h"
#include "../Debug/DebugManager.h"

static const char PLAYER_MODEL_PATH[]	
= { "data/char/Player.mv1" };								//���[�h����t�@�C����
static const float PLAYER_RADIUS = 2.5f;					//�v���C���[�̔��a

static constexpr float PLAYER_WIDTH = 10.0f;					//�v���C���[�̉��T�C�Y
static constexpr float PLAYER_HEIGHT = 18.0f;					//�v���C���[�̏c�T�C�Y
static constexpr float PLAYER_DEPTH = 10.0f;					//�v���C���[�̉��s��
static constexpr float PLAYER_HALF_HEIGHT = 9.0f;				//�v���C���[�̍����̔����̑傫��
static constexpr float PLAYER_HALF_WIDHT = 5.0f;				//�v���C���[�̉����̔����̑傫��
static constexpr int   PLAYER_DIR_NUM = 6;						//�v���C���[�̌����̐�

class CPlayer : public CModel
{
private:
	//�A�j���[�V�����ꗗ
	enum tagAnim {
		ANIMID_WAIT,			//�Ԃ�Ԃ�
		ANIMID_RUN,				//�����胂�[�V����
		ANIMID_FAST_RUN,		//���胂�[�V����
		ANIMID_RUNNINGJUMP,		//����W�����v���[�V����
		ANIMID_JUMP,			//�W�����v���[�V����
		ANIMID_DIVINGJUMP,		//�_�C�r���O�W�����v���[�V����
		ANIMID_TPOSE,			//�s�|�[�Y
		ANIMID_UPDOWN,			//���˂��ˏ㉺
		ANIMID_SHAKE,			//���U��
		ANIMID_PIANO,			//�s�A�m�������ėv����ۂ�
		ANIMID_DANCE,			//�x���Ă�
		ANIMID_DEFAULT,			//�f�t�H���g���[�V����
		ANIMID_HIDE,			//�B��Ă�

		ANIMID_NUM				//�S�A�j���[�V������
	};

	//�����Ă������
	enum tagDir {
		UP = 0,		//�����
		DOWN,		//������
		LEFT,		//������
		RIGHT,		//�E����
		FRONT,		//�O��
		BACK,		//���
	
	};

	tagDir m_eDir;					//�v���C���[�̕���

	int m_PadXBuf;					//�p�b�h���o�[�̍��E�̓��͏�Ԃ��i�[����ϐ�
	int m_PadYBuf;					//�p�b�h���o�[�̏㉺�̓��͏�Ԃ��i�[����ϐ�
	
	float m_fChangeRot;				//�v���C���[�̕�������������]������p�̕ϐ�
	float m_fRot;					//��]�l
	float m_fGravity;				//�v���C���[�̏d��

	//�t���O
	bool m_bIsHit;					//�v���C���[�����̂ɓ������Ă��邩�ǂ���
	bool m_bIsHitSide;				//�v���C���[�����̂Ɖ������œ���������
	bool m_bIsHitLength;			//�v���C���[�����̂Əc�����œ���������
	bool m_bIsGround;				//�v���C���[���n�ʂɂ������ǂ���
	bool m_bIsKeyHit;				//�L�[�����������ǂ���
	bool m_bIsHitHideObject;		//�B���悤�̃I�u�W�F�N�g�Ƃ����������ǂ���
	bool m_bIsHide;					//�n�C�h���[�h���ǂ�����Ԃ�
	bool m_bIsParkourObject;		//�p���N�[���I�u�W�F�N�g�ɂ����������ǂ���
	bool m_bIsPlayAnimation;		//�A�j���[�V�������Đ��������ǂ���
	bool m_bIsSpecifiedPos;			//�w��̏ꏊ�ɗ������ǂ���
	bool m_bIsJump;					//�W�����v�������ǂ���

	//�p���N�[���I�u�W�F�N�g4�����t���O
	

public:
	//�R���X�g���N�^
	CPlayer();
	~CPlayer();
	float m_fMoveSpeed;				//�v���C���[�̃X�s�[�h

public:
	//�����l�ݒ�
	void InitValue();
	//�ʏ폈��
	void Step(CShotManager& cShotManager, CCameraManager& cCameraManager);
	//�X�V�����f�[�^�𔽉f������
	void Update();
	//�`�揈��
	void Draw();
	//���쏈��
	void Control(VECTOR vRot);
	//�W�����v����
	void Jamp(VECTOR vRot);
	//�f�[�^�֘A�̔j��
	void Delete();
	//�I������
	void Fin();

public:
	//�t���O
	//�����t���O�̐ݒ�E�擾
	void SetIsAllive(bool bflag) { m_IsAllive = bflag; }						//�����t���O�̐ݒ�
	bool GetIsAllive() { return m_IsAllive; }									//�����t���O�̎擾

	//�W�����v�t���O�擾�E�ݒ�
	void SetIsJamp(bool bflag) { m_bIsGround = bflag; }							//�W�����v�t���O�ݒ�
	bool GetIsJamp() { return m_bIsGround; }										//�W�����v�t���O�擾

	//�B���悤�I�u�W�F�N�g�Ɠ����������ǂ���
	void SetIsHitHideObject(bool bflag) { m_bIsHitHideObject = bflag; }			//�B���悤�̃I�u�W�F�N�g�Ƃ����������ǂ����t���O�ݒ�
	bool GetIsHitHideObject()			{ return m_bIsHitHideObject; }			//�B���悤�̃I�u�W�F�N�g�Ƃ����������ǂ����t���O�擾

	//�n�C�h���[�h���ǂ���
	bool GetIsHide()					{ return m_bIsHide; }					//�n�C�h���[�h�擾

public:
	//�L�[�{�[�h����
	void Control_KeyBord(VECTOR vRot);
	//�����������߂�
	void ReflectCollision(VECTOR vAddVec);
	//���X�e�B�b�N�̊p�x�ɂ��킹�ăv���C���[����]������
	void PadRotation(VECTOR vCameraRot);
	//�ړ��x�N�g��
	void CalcMoveVec(VECTOR vCameraRot);
	//���W�Ɉړ��ʂ����Z
	void AddMove();


	float Camera, Player;
public:
	//��Ԃ��Ƃ̏���
	//�ҋ@
	void WaitCalc();
	//������
	void RunCalc();
	//�_�b�V��
	void FastRunCalc();
	//�W�����v
	void JumpCalc();
	//�_�C�r���O�W�����v
	void DivingJumpCalc();

	//�d�͌v�Z
	void Gravity();
	//�p���N�[���d��
	void ParkourGravity();


public:
	//�w��̏ꏊ�Ɉړ�
	VECTOR MoveIocationSpecification(VECTOR _startPos, VECTOR _endPos);

	//�w��̏ꏊ������
	VECTOR RotetoSpecifiedPos(VECTOR vEndPos, VECTOR vStartPos, VECTOR& vRot, VECTOR vSpd, float RotetoSpd);

public:
	//�p���N�[��
	void ParkourMotion(VECTOR vPos,float Gravity);

	//�p���N�[���n��
	void ParkourBegin(VECTOR vStartPos, VECTOR vSpd);
	//�p���N�[���r��
	void ParkourMiddle(VECTOR ObjectPos);
	//�p���N�[���I��
	void ParkourFin();

public:
	//�R���g���[���[����//
	//���ׂĂ̏�ԂŎg���鑀��
	void PadControl_AllState();
	//�����葀��
	void PadControl_Run();
	//�_�b�V���W�����v����


	////�L�[�{�[�h����
	//void KeyBordControl_Default();
	//void KeyBordControl_Run();
	//void KeyBordControl_FastRun();
	//void KeyBordControl_Jump();

public:
	//�擾
	//�i��ł�������`�F�b�N
	void GetMoveDir(bool* _DirArray);	
	//������ς���
	void ChangeDir(int FreamCnt);

	//���W�擾
	inline VECTOR	GetPosition()					{ return m_vPos; }			//�v���C���[�̍��W
	inline VECTOR	GetNextPosVec()					{ return m_vNextPos; }		//�v���C���[�̈ړ���̍��W
	inline void		GetPosition(VECTOR &vPos)		{  vPos = m_vPos; }			//�v���C���[�̍��W
	inline void		GetNextPosVec(VECTOR& vPos)		{ vPos = m_vNextPos; }		//�v���C���[�̈ړ���̍��W


	//Y���p�x�擾
	inline VECTOR	GetRotate() { return m_vRot; }
	inline VECTOR	GerViwPoint() { return m_vRot; }

	//���a�擾
	inline float	GetRadius() { return PLAYER_RADIUS; }

	void			GetHalfSize(VECTOR& vHalfSize)		{ vHalfSize = DivVec(m_vSize, 2.0f); }								//�����̃T�C�Y���擾
	VECTOR			GetSpd()							{ return m_vSpd; }													//�v���C���[�̑������擾
	float			GetfSpd()							{ return m_fMoveSpeed; }											//�X�s�[�h���擾(float)
	void			GetSize(VECTOR& vSize)				{ vSize = m_vSize; }												//�c�A���A���s���̃T�C�Y�擾
	void			GetCenterPos(VECTOR& vPos)			{ vPos = VAdd(m_vPos, VGet(0.0f, PLAYER_HALF_HEIGHT, 0.0f)); }		//�v���C���[�̒��S���W��ݒ�
	VECTOR			GetForcsPos();																							//�v���C���[�J�����ɓn�������_���W

	//�ݒ�
public:
	//���W�ݒ�
	void SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void SetPosX(float vPosX);								//X���W
	void SetPosY(float vPosY);								//Y���W
	void SetPosZ(float vPosZ);								//Z���W
	void SetNextPosVec(VECTOR vPos) { m_vNextPos = vPos; }	//�ړ���̍��W
	void SetNextPosX(float vNextPosX);						//�ړ����X���W
	void SetNextPosY(float vNextPosY);						//�ړ����Y���W
	void SetNextPosZ(float vNextosZ);						//�ړ����Z���W
	//�T�C�Y�ݒ�
	VECTOR SetSize();
		
	//���̂ɂ����Ă��邩�ǂ���
	void SetIsHit(bool flag)					{  m_bIsHit = flag; }	
	void SetIsHitSide(bool flag)				{  m_bIsHitSide = flag; }
	void SetIsHitLength(bool flag)				{  m_bIsHitLength = flag; }
	void SetIsHitParkourObject(bool flag)		{ m_bIsParkourObject = flag; }
	
	//����������
	void RessetSpeed();

private:
	//��Ԃ��Ƃ̏���
	//�f�t�H���g�̏���
	void ExecDefault();
	//�������Ă��Ȃ���
	void ExecWait(VECTOR vRot);
	//������
	void ExecRun(VECTOR vRot);
	//���蒆
	void ExecFastRun(VECTOR vRot);
	//�W�����v
	void ExecJump(VECTOR vRot);
	//�_�b�V���W�����v
	void ExecRunningJump(VECTOR vRot);
	//�_�C�r���O�W�����v
	void ExecDivingJump();
	//�n�C�h���[�h
	void ExecHide();
	////���˂��˒�
	//void ExecUpDown();
	////���U��
	//void ExecShake();
	////�s�A�m�H
	//void ExecPiano();
	////�_���X��
	//void ExecDance();
};
