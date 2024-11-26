#pragma once
#include "DxLib.h"
#include "../Manager/EnemyManager.h"
#include "../../Debug/DebugManager.h"

constexpr int AROUND_SPHERE_NUM = 3;

enum Dir
{
	RIGHT,			//右
	LEFT,			//左
	FRONT,			//前
};

struct SSphere
{
	VECTOR m_vPos;			//座標
	float  m_fRad;			//半径
};

class CAroundCollision
{
private:
	SSphere m_sSphere[AROUND_SPHERE_NUM];

public:
	// 初期化
	void Init();
	// 更新処理
	void Update();

public:
	//当たり判定後の戻し処理
	void ReflectCollision();
};