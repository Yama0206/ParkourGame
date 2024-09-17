#pragma once
#include "../Read.h"

using namespace std;

//enum eType
//{
//	Coin = 1,
//	b, 
//	c,
//	d,
//};

struct SCoin
{
	VECTOR m_vPos;		//���W
	VECTOR m_vRot;		//��]�l
	VECTOR m_vSize;		//�傫��
	VECTOR m_vScale;	//�g�k��

	bool m_IsAllive;		//�����t���O

	Type m_eType;		//���
};

class CReadItemList : public CRead
{
private:
	SCoin m_sItemData;		//�A�C�e���̏�񂪓������\����

public:
	//�A�C�e���̏������郊�X�g
	vector<SCoin> itemInfoList;

	//�A�C�e������ǂݍ���
	void ReadFile();
};
