#pragma once
#include "../Read.h"

//��`
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//�G���̃e�L�X�g�t�@�C���p�X
const int  ENEMY_STRUCT_X_NUM = 5;								//�G�\���̂̔z��̗�
const int  ENEMY_STRUCT_Y_NUM = 5;								//�G�\���̂̔z��̍s��


enum EEnemyType
{
	a = 1,
	b,
	c,
	d,
	e,

};

struct SEnemy
{
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�g��k����
	VECTOR m_vRot;			//��]�l

	EEnemyType m_eType;		//���

	int m_iHndl;			//�摜�n���h��
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemy[ENEMY_STRUCT_X_NUM][ENEMY_STRUCT_Y_NUM];		//�G�̏��\����

public:
	void ReadFile();												//�t�@�C���ǂݍ���
};
