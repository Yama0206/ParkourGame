#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"
#include <vector>

using namespace std;

struct SParkourObject
{
	VECTOR m_vPos;				//���W
	VECTOR m_vScale;			//�g�k��
	ParkourType m_eType;		//�^�C�v

	bool IsAllive;		//�����t���O
};

class ReadParkourObjectList : public CRead {

private:
	SParkourObject m_sParkourData;

public:
	vector<SParkourObject> sparkourObjectInfoList;

	//�t�@�C���ǂݍ���
	void ReadFile();

};
