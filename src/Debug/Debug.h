#pragma once

#include "DxLib.h"


class CDebug
{
private:
	

public:

	//���W�`��
	// posX : �\��X���W
	// posY : �\��Y���W
	// vPos : �\��������W
	void PrintPos(int posX, int posY, VECTOR vPos);

	//�X�s�[�h�`��
	// posX : �\��X���W
	// posY : �\��Y���W
	// fSpeed : �\������X�s�[�h
	void PrintSpeed(int posX, int posY,float fSpeed);

	//��]�l�`��
	// posX : �\��X���W
	// posY : �\��Y���W
	// fRot : �\�������]�l
	void PrintRot(int posX, int posY, float fRot);

};
