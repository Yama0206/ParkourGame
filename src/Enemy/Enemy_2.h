#pragma once
#include "Enemy.h"
#include <math.h>

class CEnemy_2 : public CEnemy
{
private:
public:
	//•‘ƒtƒŒ[ƒ€ŒÄ‚Ôˆ—
	void Step();
	//“G‚Ì”­Ëˆ—
	void Shot(CShotManager& cShotManager);
};
