#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"
#include <vector>

using namespace std;

struct SParkourObject
{
	VECTOR m_vObjectPos;		//�I�u�W�F�N�g���W
	VECTOR m_vFrontPos;			//�O�����W
	VECTOR m_vBackPos;			//�����W
	VECTOR m_vRightPos;			//�E�����W
	VECTOR m_vLeftPos;			//�������W

	ParkourType m_eType;		//�^�C�v

	bool m_IsAllive;				//�����t���O
};

class ReadParkourObjectList : public CRead {

private:
	SParkourObject m_sParkourData;

public:
	vector<SParkourObject> sparkourObjectInfoList;

	//�t�@�C���ǂݍ���
	void ReadFile();

};
