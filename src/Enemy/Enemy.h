#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"
#include "../Math/Math.h"
#include "../CheckPoint/Manager/CheckPointManager.h"

//��`
const float RADIUS = 5.0f;					//�G�̔��a				

//�G�̏��
enum EnemyState
{
	Patrol = 1,		//����
	Tracking,		//�ǐ�
};


class CEnemy
{
protected:
	VECTOR m_vPos;				//���W
	VECTOR m_vSpeed;			//�ړ����x
	VECTOR m_vRot;				//��]�l
	VECTOR m_vSize;				//�c�@���@���s���̃T�C�Y
	VECTOR m_vScale;			//�g�k��

	int m_iHndl;				//���f���n���h��
	bool m_IsActive;			//�����t���O
	float m_fRadius;			//���a

	int FrameCnt;				//�t���[���J�E���g

	EnemyState m_eState;			//�G�̏��

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemy();
	~CEnemy();

	//������
	void Init();

	//�f�[�^���[�h
	void Load(int iMdlHndl);
	//�I������
	void Fin();
	//���t���[���Ăԏ���
	void Step(VECTOR vPlayerPos);
	//�`�揈��
	void Draw();

	void TrackingPlayer(VECTOR vPlayerPos);

	//vPos		:		�������W
	//vSpeed	:		�ړ����x(�����x�N�g����)
	//@return	:		true = ���N�G�X�g���� false = ���s
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//��������
	bool IsActiv() { return m_IsActive; }
	//���W�擾
	// �Q�Ɠn��
	// vPos		:	���W��ۑ�����ϐ�
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }

	//�߂�l
	VECTOR GetPosVec() { return m_vPos; }
	VECTOR GetRotVec() { return m_vRot; }
	float GetRadius() { return m_fRadius; }

	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot, bool IsActive);
	void SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void SetRotVec(VECTOR vRot) { m_vRot = vRot; }

	void SetPosVec_X(float fPos) { m_vPos.x = fPos; }
	void SetPosVec_Y(float fPos) { m_vPos.y = fPos; }
	void SetPosVec_Z(float fPos) { m_vPos.z = fPos; }

	void SetRotVec_X(float fRot) { m_vRot.x = fRot; }
	void SetRotVec_Y(float fRot) { m_vRot.y = fRot; }
	void SetRotVec_Z(float fRot) { m_vPos.z = fRot; }

	//�X�V����
	void Update();

	//�����蔻���̏���
	void HitCalc();
};


