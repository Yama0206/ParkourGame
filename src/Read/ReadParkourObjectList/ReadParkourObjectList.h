#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"



struct SParkourObject
{
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�傫��

	bool IsAllive;		//�����t���O
};

class ReadParkourObjectList : public CRead {

private:


public:
	//�t�@�C���ǂݍ���
	void ReadFile();

};
