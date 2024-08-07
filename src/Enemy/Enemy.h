#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"

//��`
const float RADIUS = 5.0f;					//�G�̔��a				

class CEnemy
{
protected:
	VECTOR m_vPos;				//���W
	VECTOR m_vSpeed;			//�ړ����x
	VECTOR m_vRot;				//��]�l
	int m_iHndl;				//���f���n���h��
	bool m_bIsActive;			//�����t���O
	float m_fRadius;

	int FrameCnt;				//�t���[���J�E���g

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
	void Step();
	//�`�揈��
	void Draw();

	//vPos		:		�������W
	//vSpeed	:		�ړ����x(�����x�N�g����)
	//@return	:		true = ���N�G�X�g���� false = ���s
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//��������
	bool IsActiv() { return m_bIsActive; }
	//���W�擾
	// vPos		:	���W��ۑ�����ϐ�
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	float GetRadius() { return m_fRadius; }

	//�����蔻���̏���
	void HitCalc();
};


