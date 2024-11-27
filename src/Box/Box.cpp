#include "Box.h"

const char BOX_PATH[] = { "data/Box/Box.x" };

const float BOX_SIZE = 16.0f;

void CBox::Init()
{
	m_vPos = { 20.0f, 18.0f, 0.0f };
	m_vScale = { 8.0f, 8.0f ,8.0f };
	m_vSize = { 16.0f, 16.0f, 16.0f };
	m_iHndl = -1;
	isAllive = true;
}

void CBox::Load()
{
	m_iHndl = MV1LoadModel(BOX_PATH);
}
void CBox::Step() {
	if (CInput::IsKeyPush(KEY_INPUT_0)) {
		isAllive = false;
	}
	//if (CInput::IsKeyPush(KEY_INPUT_0) && !isAllive) {
	//	isAllive = true;
	//}
}

void CBox::Draw()
{
	if (isAllive) {
		MV1DrawModel(m_iHndl);
	}
}

void CBox::Update()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1SetPosition(m_iHndl, m_vPos);
}

VECTOR CBox::GetHalfSize()
{
	VECTOR vHalfSize;

	return vHalfSize = DivVec(m_vSize, 2.0f);
}
