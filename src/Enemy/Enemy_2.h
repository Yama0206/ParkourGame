#pragma once
#include "Enemy.h"
#include <math.h>

class CEnemy_2 : public CEnemy
{
private:
public:
	//���t���[���Ăԏ���
	void Step();
	//�G�̔��ˏ���
	void Shot(CShotManager& cShotManager);
};
