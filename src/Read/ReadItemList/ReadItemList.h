#pragma once
#include "../Read.h"
#include "../../Item/ItemBase/ItemBase.h"

using namespace std;


struct SItem
{
	VECTOR m_vPos;		//���W
	VECTOR m_vRot;		//��]�l
	VECTOR m_vSize;		//�傫��
	VECTOR m_vScale;	//�g�k��

	bool m_IsAllive;	//�����t���O

	eType m_eType;		//���
};

class CReadItemList : public CRead
{
private:
	SItem m_sItemData;		//�A�C�e���̏�񂪓������\����

public:
	//�A�C�e���̏������郊�X�g
	vector<SItem> itemInfoList;

	//�A�C�e������ǂݍ���
	void ReadFile();
};
