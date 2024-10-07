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


	//���a�`��
	// posX : �\��X���W
	// posY : �\��Y���W
	// fRad : �\�����锼�a
	void PrintRad(int posX, int posY, float fRad);

	//�ԍ��`��
	// posX : �\��X���W
	// posY : �\��Y���W
	// Number : �\������ԍ�
	void PrintNum(int posX, int posY, int num);

	//��������������`��
	// posX : �\��X���W
	// posY : �\��Y���W
	void HitPrint(int posX, int posY);

};
