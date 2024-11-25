#pragma once
#include "DxLib.h"
#include "../Manager/EnemyManager.h"
#include "../../Debug/DebugManager.h"

enum Dir
{
	RIGHT,			//右
	LEFT,			//左
	FRONT,			//前
};

class CAroundCollision
{
private:
	VECTOR m_vPos[3];
	float  m_fRad[3];

public:
	// 初期化
	void Init();
	// 読み込み
	void Load();
	// 更新処理
	void Update();

public:
	//当たり判定後の戻し処理
	void ReflectCollision();
};