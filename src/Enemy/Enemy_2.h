#pragma once
#include "Enemy.h"
#include <math.h>

class CEnemy_2 : public CEnemy
{
private:
public:
	//舞フレーム呼ぶ処理
	void Step();
	//敵の発射処理
	void Shot(CShotManager& cShotManager);
};
