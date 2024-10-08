#pragma once
#include "DxLib.h"
#include "../../Read/Read.h"
#include "../CheckPoint.h"
#include <vector>

using namespace std;


struct SCheckPoint
{
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�T�C�Y

	float fRad;			//���a
	int m_iCPNum;		//�`�F�b�N�|�C���g�ԍ�
	int m_NextCPNum[4];	//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
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