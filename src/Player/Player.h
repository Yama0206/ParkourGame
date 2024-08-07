#pragma once

#include "Dxlib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../shot/ShotManager.h"
#include "../Model/Model.h"
#include "../Math/Math.h"
#include "../Camera/CameraManager.h"

static const char PLAYER_MODEL_PATH[]	
= { "data/char/char.pmd" };									//���[�h����t�@�C����
static const float PLAYER_RADIUS = 2.5f;					//�v���C���[�̔��a

static const float PLAYER_WIDTH = 10.0f;					//�v���C���[�̉��T�C�Y
static const float PLAYER_HEIGHT = 18.0f;					//�v���C���[�̏c�T�C�Y
static const float PLAYER_DEPTH = 10.0f;					//�v���C���[�̉��s��
static const float PLAYER_HALF_HEIGHT = 9.0f;				//�v���C���[�̍����̔����̑傫��
static const float PLAYER_HALF_WIDHT = 5.0f;				//�v���C���[�̉����̔����̑傫��
static const int   PLAYER_DIR_NUM = 6;						//�v���C���[�̌����̐�

class CPlayer : public CModel
{
private:
	//�v���C���[�̏��
	enum tagPlayerState {
		PLAYER_STATE_NORMAL,		//�ҋ@�E������
		PLAYER_STATE_JUMP,			//�W�����v��
		PLAYER_STATE_DASH,			//���蒆

		PLAYER_STATE_NUM
	};

	//�A�j���[�V�����ꗗ
	enum tagAnim {
		ANIMID_DEFAULT,			//�f�t�H���g���[�V����
		ANIMID_WALK,			//�������[�V����
		ANIMID_RUN,				//���胂�[�V����
		ANIMID_WAIT,			//�Ԃ�Ԃ�
		ANIMID_UPDOWN,			//���˂��ˏ㉺
		ANIMID_SHAKE,			//���U��
		ANIMID_PIANO,			//�s�A�m�������ėv����ۂ�
		ANIMID_DANCE,			//�x���Ă�

		ANIMID_NUM				//�S�A�j���[�V������
	};

	//�����Ă������
	enum tagDir {
		UP = 0,		//�����
		DOWN,		//������
		LEFT,		//������
		RIGHT,		//�E����
		FRONT,		//�O����
		BACK,		//������
	
	};

	tagPlayerState m_eState;		//�v���C���[�̏��
	tagDir m_eDir;					//�v���C���[�̕���
	
	VECTOR m_ViewRot;				//�v���C���[�̌��Ă������
	float fChangeRot;				//�v���C���[�̕�������������]������p�̕ϐ�

	//�t���O
	bool m_IsHit;			//�v���C���[�����̂ɓ������Ă��邩�ǂ���
	bool m_IsHitSide;		//�v���C���[�����̂Ɖ������œ���������
	bool m_IsHitLength;		//�v���C���[�����̂Əc�����œ���������
	bool m_IsJump;			//�v���C���[���W�����v�������ǂ���
	bool m_IsKeyHit;		//�L�[�����������ǂ���

public:
	//�R���X�g���N�^
	CPlayer();
	~CPlayer();

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
	void Jamp();
	//�d�͌v�Z
	void Gravity();
	//�e�̔��ˏ���
	void Shot(CShotManager& cShotManager);

	//���W�ݒ�
	VECTOR SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void   SetPosX(float vPosX);					//X���W
	void   SetPosY(float vPosY);					//Y���W
	void   SetPosZ(float vPosZ);					//Z���W
	void   SetNextPosX(float vNextPosX);			//�ړ����X���W
	void   SetNextPosY(float vNextPosY);			//�ړ����Y���W
	void   SetNextPosZ(float vNextosZ);				//�ړ����Z���W
	//�T�C�Y�ݒ�
	VECTOR SetSize();

	//�f�[�^�֘A�̔j��
	void Delete();
	//�I������
	void Fin();

	//�擾�E�ݒ�֘A
	//�i��ł�������`�F�b�N
	void GetMoveDir(bool* _DirArray);	
	//������ς���
	void ChangeDir(int FreamCnt);

	//���W�擾
	inline VECTOR GetPosition() { return m_vPos; }
	inline void GetPosition(VECTOR &vPos) {  vPos = m_vPos; }
	inline void GetNextPosVec(VECTOR& vPos) { vPos = m_vNextPos; }

	//Y���p�x�擾
	inline VECTOR GetRotate() { return m_vRot; }
	//���a�擾
	inline float GetRadius() { return PLAYER_RADIUS; }

	tagPlayerState GetPlayerState()			{ return m_eState; }	//�v���C���[�̏�Ԃ��擾
	void GetHalfSize(VECTOR& vHalfSize);							//�����̃T�C�Y���擾
	void GetSpd(VECTOR& vSpd)				{ vSpd = m_vSpd; }		//�v���C���[�̑������擾
  VECTOR GetSpd()							{ return m_vSpd; }		//�v���C���[�̑������擾
	void GetCenterPos(VECTOR& vPos);								//�v���C���[�̒��S���W��ݒ�
	void GetSize(VECTOR& vSize);									//�c�A���A���s���̃T�C�Y�擾

	//���̂ɂ����Ă��邩�ǂ���
	bool SetIsHit(bool flag) { return m_IsHit = flag; }	
	bool SetIsHitSide(bool flag) { return m_IsHitSide = flag; }
	bool SetIsHitLength(bool flag) { return m_IsHitLength = flag; }

	//�����t���O�̐ݒ�E�擾
	void SetIsAllive(bool flag) { m_IsAllive = flag; }			//�����t���O�̐ݒ�
	bool GetIsAllive() { return m_IsAllive; }					//�����t���O�̎擾

	//�W�����v�t���O�擾�E�ݒ�
	void SetIsJamp(bool flag) { m_IsJump = flag; }				//�W�����v�t���O�ݒ�
	bool GetIsJamp() { return m_IsJump; }						//�W�����v�t���O�擾

private:
	//�������Ă��Ȃ��Ƃ��̏���
	void ExecDefault();
	//������
	void ExecWalk();
	//���蒆
	void ExecRun();
	////�ҋ@��
	//void ExecWait();
	////���˂��˒�
	//void ExecUpDown();
	////���U��
	//void ExecShake();
	////�s�A�m�H
	//void ExecPiano();
	////�_���X��
	//void ExecDance();
};
