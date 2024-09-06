#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>

const int  MAP_CHIP_X_NUM = 10;		//�}�b�v�`�b�v���̐�
const int  MAP_CHIP_Y_NUM = 1;		//�}�b�v�`�b�v�c�̐�

const int TYPE_NUM = 256;					//�e�X�g�^�C�v�̔z��̐�
const int PATH_NUM = 256;					//�e�X�g�p�X�̔z��̐�


enum Type
{
	a = 1,
	b, 
	c,
	d,
};

struct s_List
{
	VECTOR m_vPos;
	VECTOR m_vSize;

	char m_cType[TYPE_NUM];
	char m_cPath[PATH_NUM];
};



class CRead
{
private:
	s_List m_Test;
	Type eType;

	int mapIndex;			//�ǂݍ��ރI�u�W�F�N�g�̍\���̂̔z��̔ԍ�

	//�}�b�v�`�b�v���i�[���ꂽ�ϐ�
	int m_FileReadMapData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];

public:
	//������
	void Init();

	//�t�@�C���ǂݍ���
	void ReadFile();
	//�t�@�C���̏�������
	void SaveFile();

	//�f�o�b�O�p�`��
	void Draw();

	//csv�̒l���擾
	int GetFileReadMapData(int x_index, int y_index) { return m_FileReadMapData[y_index][x_index]; }


};
