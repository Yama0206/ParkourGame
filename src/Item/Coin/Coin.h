#pragma once
#include "DxLib.h"
#include "../../Object/Object.h"
#include <iostream>
#include <vector>

class CCoin : public CObject
{
private:

public:
	//’Êíˆ—
	void Step();

	void SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale);
};
