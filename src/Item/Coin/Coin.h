#pragma once
#include "DxLib.h"
#include "../../Item/ItemBase/ItemBase.h"
#include <iostream>
#include <vector>

class CCoin : public CItemBase
{
private:

public:
	//�ʏ폈��
	void Step();

	void SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale, VECTOR vSize, eType eType,int IsAllive);
};
