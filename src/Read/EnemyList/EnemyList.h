#pragma once
#include "../Read.h"
#include <iostream>
#include <list>

using namespace std;

//��`
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//�G���̃e�L�X�g�t�@�C���p�X

struct SEnemy
{
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�g��k����
	VECTOR m_vRot;			//��]�l
	VECTOR m_vSpeed;		//����

	Type m_eType;			//���
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemyData;		//�G�̏��\����

public:
	//�ǂݍ��݃f�[�^���X�g
	list<SEnemy> enemyInfoList;

	//�t�@�C���ǂݍ���
	void ReadFile();																	//�t�@�C���ǂݍ���

	SEnemy GetStructEnemy(SEnemy& Enemy, int num) { return Enemy = enemyInfoList; }		//�G���̍\���̂��擾

};
