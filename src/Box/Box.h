#pragma once
#include "DxLib.h"
#include "../Input/Input.h"
#include "../Math/Math.h"

const float BOX_RADIUS = 8.0f;

class CBox
{
protected:
	VECTOR m_vPos;
	VECTOR m_vSize;
	VECTOR m_vScale;
	int m_iHndl;
	bool isAllive;

public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Update();

	VECTOR GetPotision(VECTOR &vPos) { return vPos = m_vPos; }
	VECTOR GetSize() { return m_vSize; }
	VECTOR GetHalfSize();
	float GetRadius() { return BOX_RADIUS; }
};
