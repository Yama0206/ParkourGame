#include "Goal.h"

void CGoal::Init()
{
	m_vPos = { 0.0f, 35.0f, 800.0f };
	m_vScale = { 0.1, 0.1f ,0.1f };
	m_vSize = { GOAL_X_SIZE, GOAL_Y_SIZE, GOAL_Z_SIZE };
	m_iHndl = -1;
	isAllive = true;
	m_IsGoal = false;
}


void CGoal::Load()
{
	m_iHndl = MV1LoadModel(GOAL_PATH);
}

void CGoal::Step() {
}

void CGoal::Draw()
{
	if (isAllive) {
		MV1DrawModel(m_iHndl);
	}
}

void CGoal::Update()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1SetPosition(m_iHndl, m_vPos);
}
