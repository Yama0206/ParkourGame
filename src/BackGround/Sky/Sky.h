#pragma once
#include "DxLib.h"
#include "../BackGround.h"

const char SKY_IMG_PATH[] = { "data/Sky/Sky.x" };

class CSky
{
private:
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�T�C�Y
	VECTOR m_vScale;		//�g�k��
	VECTOR m_vRot;			//��]�l

	int m_ImgHndl;			//�摜�n���h��
public:

	void Init();

	//�ǂݍ���
	void Load();

	//�ʏ폈��
	void Step(); 

	//�`�揈��
	void Draw();

	//�X�V����
	void UpDate();

	//�I������
	void Fin();
};
