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
	VECTOR m_vSize;				//�g�k��

	int m_iHndl;				//���f���n���h��
	bool m_IsActive;			//�����t���O
	float m_fRadius;			//���a

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
	bool IsActiv() { return m_IsActive; }
	//���W�擾
	// vPos		:	���W��ۑ�����ϐ�
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	float GetRadius() { return m_fRadius; }

	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot);

	//�����蔻���̏���
	void HitCalc();
};


