#pragma once
#include "DxLib.h"
#include "../Math/Math.h"
#include "../Input/Input.h"

//’è‹`
const float GOAL_X_SIZE = 30.0f;
const float GOAL_Y_SIZE = 70.0f;
const float GOAL_Z_SIZE = 30.0f;

const char GOAL_PATH[] = {"data/Goal/Goal.mv1"};

class CGoal {
	VECTOR m_vPos;
	VECTOR m_vSize;
	VECTOR m_vRot;
	VECTOR m_vScale;
	int m_iHndl;
	bool isAllive;
	bool m_IsGoal;

public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Update();

	VECTOR GetPotision(VECTOR& vPos) { return vPos = m_vPos; }
	VECTOR GetCenterPos(VECTOR& vPos, float UpValue) { return vPos = VGet(m_vPos.x, m_vPos.y + UpValue, m_vPos.z); }
	VECTOR GetSize() { return m_vSize; }
	VECTOR GetRadius() { return DivVec(m_vSize, 2); }
	bool GetIsGoal() { return m_IsGoal; }
	void SetIsGoal(bool flag) { m_IsGoal = flag; }
};
