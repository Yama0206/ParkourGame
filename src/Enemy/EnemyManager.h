#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Enemy_2.h"

#define ENEMY_NUM		(50)

class CEnemyManager
{
private:
	//�G�A�G�̃^�C�v��������Ƃ����̃N���X�������Ă���
	//�{���̓������̓��I�m�ۂ��]�܂���
	CEnemy m_cEnemy[ENEMY_NUM];
	//CEnemy_2 m_cEnemy_2[ENEMY_NUM];
	
	int m_iWaitCnt;		//�G�����������܂ł̎���
	int m_iWaitCnt_2;	//2�̖ڂ̓G�����������܂ł̎���	

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyManager();
	~CEnemyManager();

	//������
	void Init();
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

