#pragma once
#include "../Read.h"

//��`
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//�G���̃e�L�X�g�t�@�C���p�X
const int  ENEMY_STRUCT_NUM = 5;								//�G�\���̂̔z��̐�

struct SEnemy
{
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�g��k����
	VECTOR m_vRot;			//��]�l

	Type m_eType;			//���

	int m_iHndl;			//�摜�n���h��
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemy[ENEMY_STRUCT_NUM];		//�G�̏��\����

public:
	void ReadFile();														//�t�@�C���ǂݍ���

	SEnemy GetStructEnemy(SEnemy& Enemy) { return Enemy; }		//�G���̍\���̂��擾

};
