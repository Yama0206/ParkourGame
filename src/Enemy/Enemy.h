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
	void Step(VECTOR vPlayerPos, VECTOR vPos, int Index);
	//�`�揈��
	void Draw();

	//�v���C���[��ǐՂ���
	void TrackingPlayer(VECTOR vPlayerPos);

	//�`�F�b�N�|�C���g�Ɉړ�����
	void TrackingCheckPoint();

	//vPos		:		�������W
	//vSpeed	:		�ړ����x(�����x�N�g����)
	//@return	:		true = ���N�G�X�g���� false = ���s
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//��������
	bool IsActiv() { return m_IsActive; }
	//���W�擾
	// vPos		:	���W��ۑ�����ϐ�
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	float GetRadius() { return m_fRadius; }

	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot, bool IsActive);

	//�X�V����
	void Update();

	//�����蔻���̏���
	void HitCalc();
};


