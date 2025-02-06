#pragma once
#include "../../Read/Read.h"

using namespace std;

class CReadJumpObjectManager
{
private:
	struct SJumpObject
	{
		VECTOR m_vPos;		//���W
		VECTOR m_vRot;		//��]�l
		VECTOR m_vSize;		//�傫��
		VECTOR m_vScale;	//�g�k��

		bool m_IsAllive;	//�����t���O
	};

	SJumpObject m_sItemData;		//�A�C�e���̏�񂪓������\����

public:
	//�A�C�e���̏������郊�X�g
	vector<SJumpObject> jumpobjectList;

	//�A�C�e������ǂݍ���
	void ReadFile();

};