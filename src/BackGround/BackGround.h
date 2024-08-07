#pragma once
#include "DxLib.h"

const char BACKGROUND_PATH[] = { "data/field/LavaField.mv1" };
const float BACKGROUND_X_SIZE = 500.0f;								//X�T�C�Y
const float BACKGROUND_Y_SIZE = 0.0f;								//Y�T�C�Y
const float BACKGROUND_Z_SIZE = 500.0f;								//Z�T�C�Y
const float BACKGROUND_X_SCALE = 0.5f;								//X�̊g��k����
const float BACKGROUND_Y_SCALE = 0.5f;								//Y�̊g��k����
const float BACKGROUND_Z_SCALE = 0.5f;								//Z�̊g��k����

class BackGround
{
protected:
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�T�C�Y
	VECTOR m_vScale;		//�g�k��
	int m_ImgHndl;			//�摜�n���h��

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

	//�t�B�[���h�̍��W�擾
	VECTOR GetPos() { return m_vPos; }

	//�t�B�[���h�̃T�C�Y�擾
	VECTOR GetSize() { return m_vSize; }
};
