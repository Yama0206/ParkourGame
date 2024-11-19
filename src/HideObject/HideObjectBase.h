#pragma once
#include "DxLib.h"
#include "../Object/Object.h"
#include <vector>

enum Type
{
	Locker,
};

class HideObjectBase : public CObject
{
private:
	Type m_eType;			

public:
	void SetInfo(VECTOR vPos, VECTOR vScale, VECTOR vRot, Type eType);

};
