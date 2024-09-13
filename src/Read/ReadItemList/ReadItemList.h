#pragma once
#include "../Read.h"

using namespace std;

struct SCoin
{
	VECTOR m_vPos;		//���W
	VECTOR m_vRot;		//��]�l
	VECTOR m_vScale;	//�g�k��

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
