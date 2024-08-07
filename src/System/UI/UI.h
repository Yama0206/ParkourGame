#pragma once
#include "DxLib.h"

//��`
const int TIME_IMAGE_NUM = 10;

struct STime {
	VECTOR m_vPos;
	VECTOR m_vScale;

	int m_iHndl[TIME_IMAGE_NUM];
};

class CUI
{
private:
	//�\����
	static STime m_sTime;		// ���ԕ\��UI


public:
	//������
	static void Init();
	//�ǂ݂���
	static void Load();
	//�I������
	static void Exit();

	// ���ԕ\���֐�
	static void DrawTime();
};
