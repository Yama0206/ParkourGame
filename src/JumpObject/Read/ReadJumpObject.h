#pragma once
#include "../../Read/Read.h"

using namespace std;

//enum Type
//{
//	a,
//	b, 
//	c,
//};

class CReadJumpObject
{
private:
	struct SJumpObject
	{
		VECTOR m_vPos;		//���W
		VECTOR m_vRot;		//��]�l
		VECTOR m_vSize;		//�傫��
		VECTOR m_vScale;	//�g�k��

	/*	Type m_eType;*/

		bool m_IsAllive;	//�����t���O
	};

	SJumpObject m_sJumpObjectData;		//�A�C�e���̏�񂪓������\����

public:
	//�A�C�e���̏������郊�X�g
	vector<SJumpObject> jumpobjectList;

	//�A�C�e������ǂݍ���
	void ReadFile();

};