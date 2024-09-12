#pragma once
#include "DxLib.h"

class CObject
{
protected:
	VECTOR m_vPos;		//���W
	VECTOR m_vRot;		//��]�l
	VECTOR m_vSize;		//�c�@���@���s���̃T�C�Y
	VECTOR m_vScale;	//�g�k��

	int m_iHndl;		//�摜�n���h��
	bool m_IsAllive;	//�����t���O


public:
	//������
	void Init();
	//�ǂݍ���
	void Load(int iMdHndl);
	//�ʏ폈��
	void Step();
	//�`��
	void Draw();
	//�I������
	void Fin();
	//�X�V����
	void Update();

public:
	//��������
	void SetInfo(VECTOR vPos, VECTOR vSize, VECTOR vRot);

};
