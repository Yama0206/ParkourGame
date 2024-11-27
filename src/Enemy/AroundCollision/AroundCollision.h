#pragma once
#include "DxLib.h"
#include "../Manager/EnemyManager.h"
#include "../../Debug/DebugManager.h"

constexpr int AROUND_SPHERE_NUM = 3;

enum Dir
{
	RIGHT,			//�E
	LEFT,			//��
	FRONT,			//�O
};

struct SSphere
{
	VECTOR m_vPos;			//���W
	float  m_fRad;			//���a
};

class CAroundCollision
{
private:
	SSphere m_sSphere[AROUND_SPHERE_NUM];

public:
	// ������
	void Init();
	// �����蔻���������ʒu��ݒ�
	void SetAroundCollisionInfo(VECTOR vCenterPos);

public:
	//�����蔻���̖߂�����
	void ReflectCollision();
};