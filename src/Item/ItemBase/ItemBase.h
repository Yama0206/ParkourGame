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
	void SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vSize, VECTOR vScale, int IsAllive);

	//�X�V����
	void Update();

	//�擾
	VECTOR GetPosVec() { return m_vPos; }		//���W�擾
	VECTOR GetSizeVec() { return m_vSize; }		//�T�C�Y�擾

};