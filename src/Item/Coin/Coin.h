#pragma once
#include "DxLib.h"
#include "../../Item/ItemBase/ItemBase.h"
#include <iostream>
#include <vector>

class CCoin : public CItemBase
{
private:

public:
	//’Êíˆ—
	void Step();

	void SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale);
};
