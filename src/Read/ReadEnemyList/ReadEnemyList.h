#pragma once
#include "../Read.h"
#include <iostream>
#include <vector>

using namespace std;

//��`
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//�G���̃e�L�X�g�t�@�C���p�X

struct SEnemy
{
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�c�@���@���䂫�T�C�Y
	VECTOR m_vRot;			//��]�l
	VECTOR m_vSpeed;		//����
	VECTOR m_vScale;		//�g�k��

	Type m_eType;			//���
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemyData;		//�G�̏��\����

public:
	//�ǂݍ��݃f�[�^���X�g
	vector<SEnemy> enemyInfoList;

	//�t�@�C���ǂݍ���
	void ReadFile();			
};