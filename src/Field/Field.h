#pragma once
#include "DxLib.h"

const char FIELD_PATH[] = { "data/field/KariMap.mv1" };
const float FIELD_X_SIZE = 500.0f;								//X�T�C�Y
const float FIELD_Y_SIZE = 0.0f;								//Y�T�C�Y
const float FIELD_Z_SIZE = 500.0f;								//Z�T�C�Y
const float FIELD_X_SCALE = 0.5f;								//X�̊g��k����
const float FIELD_Y_SCALE = 0.5f;								//Y�̊g��k����
const float FIELD_Z_SCALE = 0.5f;								//Z�̊g��k����

class CField
{
protected:
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�T�C�Y
	VECTOR m_vScale;		//�g�k��

	int m_iHndl;			//�摜�n���h��
	bool m_IsHitFrag;		//�����������ǂ���

public:
	//������
	void Init();
	//�ǂݍ���
	void Load();
	//�ʏ폈��
	void Step();
	//�`��
	void Draw();
	//�X�V����
	void UpDate();
	//�I������
	void Fin();


	//�X�V����
	VECTOR HitCheck(VECTOR vCenter, float fRadius);

	//�t�B�[���h�̍��W�擾
	VECTOR GetPos() { return m_vPos; }

	//�t�B�[���h�̃T�C�Y�擾
	VECTOR GetSize() { return m_vSize; }
};
