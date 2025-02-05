#pragma once
#include "../Object/Object.h"


class CJumpObject : public CObject
{
private:
	bool IsHit;			//‚ ‚Á‚½‚©‚Ç‚¤‚©
public:
	//‰Šúİ’è
	void InitValue();
	//’Êíˆ—
	void Step();
};