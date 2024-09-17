#pragma once
#include "DxLib.h"

enum eType
{
	Coin = 1,

};


class CItemBase
{
protected:
	VECTOR m_vPos;		//���W
	VECTOR m_vRot;		//��]�l
	VECTOR m_vSize;		//���f���T�C�Y
	VECTOR m_vScale;	//�g�k��
	
	int m_iHndl;		//���f���n���h��
	bool m_IsAllive;	//�����t���O

	int iAngleCnt;		//�A�C�e������]����Ƃ��̃J�E���g�ϐ�

public:
	//�ǂݍ���
	void Load(int iModelHndl);
	//�`��
	void Draw();

 	//��������
	void SetInfo(VECTOR vPos, VECTOR vSize, VECTOR vRot);

	void Update();
};