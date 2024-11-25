#pragma once
#include "DxLib.h"
#include "../Manager/EnemyManager.h"
#include "../../Debug/DebugManager.h"

enum Dir
{
	RIGHT,			//�E
	LEFT,			//��
	FRONT,			//�O
};

class CAroundCollision
{
private:
	VECTOR m_vPos[3];
	float  m_fRad[3];

public:
	// ������
	void Init();
	// �ǂݍ���
	void Load();
	// �X�V����
	void Update();

public:
	//�����蔻���̖߂�����
	void ReflectCollision();
};