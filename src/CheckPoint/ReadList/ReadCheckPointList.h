#pragma once
#include "DxLib.h"
#include "../../Read/Read.h"
#include <vector>

using namespace std;

struct SCheckPoint
{
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�T�C�Y

	float fRad;			//���a
};


class CReadCheckPointList
{
private:
	//�`�F�b�N�|�C���g�̏�񂪓������\����
	SCheckPoint m_CheckPointData;
public:
	//�`�F�b�N�|�C���g�̏�������
	vector <SCheckPoint> checkPointList;

	//�f�[�^�ւ̓ǂݍ���
	void ReadFile();
};