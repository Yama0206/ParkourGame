#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Boss/NormalBoss.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include "../Read/ReadEnemyList/ReadEnemyList.h"
#include <iostream>
#include <vector>

using namespace std;

#define ENEMY_NUM		(50)


class CEnemyManager
{
private:
	//�G�A�G�̃^�C�v��������Ƃ����̃N���X�������Ă���
	//�{���̓������̓��I�m�ۂ��]�܂���
	vector<CEnemy*>m_cEnemyList;
	
	//�G����ǂݍ��ނ��߂̃N���X
	CEnemyRead m_cEnemyRead;

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
	void Step(VECTOR vPlayerPos);
	//�`�揈��
	void Draw();
	//�X�V����
	void Update();

public:
	//�G���擾
	inline CEnemy* GetEnemy(int iID) { return m_cEnemyList[iID]; }
	//�N���X�̃T�C�Y�擾
	int GetEnemySize() { return m_cEnemyList.size(); }

	//�G���N�G�X�g
	void RequestEnemy();

};

