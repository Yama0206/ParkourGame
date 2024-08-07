#pragma once
#include <DxLib.h>

class CShot
{
private:
	VECTOR m_vPos;				//���W
	VECTOR m_vSpeed;			//�ړ����x
	int m_iHndl;				//���f���n���h��
	float m_fRadius;				//���a

	bool m_bIsActive;			//�����t���O

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CShot();
	~CShot();

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
	bool RequestShot(const VECTOR& vPos, const VECTOR& vSpeed);
	//��������
	bool IsActiv() { return m_bIsActive; }

	//���W�擾
	void GetPotision(VECTOR& vPos) { vPos = m_vPos; }
	//���a�擾
	float GetRadius() { return m_fRadius; }

	//�����蔻���̏���
	void HitCalc();
};
