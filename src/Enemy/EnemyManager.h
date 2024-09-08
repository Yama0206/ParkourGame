#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Enemy_2.h"
#include "../Read/EnemyList/EnemyList.h"

#define ENEMY_NUM		(50)

class CEnemyManager
{
private:
	//�G�A�G�̃^�C�v��������Ƃ����̃N���X�������Ă���
	//�{���̓������̓��I�m�ۂ��]�܂���
	CEnemy m_cEnemy[ENEMY_NUM];
	
	//�G����ǂݍ��ނ��߂̃N���X
	CEnemyRead m_cEnemyRead;


	int m_iWaitCnt;		//�G�����������܂ł̎���
	int m_iWaitCnt_2;	//2�̖ڂ̓G�����������܂ł̎���	

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyManager();
	~CEnemyManager();

	//������
	void Init();
	//�����l�ݒ�
	void InitValue();
	//�f�[�^���[�h
	void Load();
	//�I������
	void Fin();
	//�J��Ԃ��s������
	void Step();
	//�`�揈��
	void Draw();

	//�G���擾
	inline CEnemy& GetEnemy(int iID) { return m_cEnemy[iID]; }

	//�G���N�G�X�g
	void RequestEnemy();

};

