#include "FootBox.h"

void CFootBox::Init()
{
	m_vPos = { 0.0f, 0.0f, 0.0f };
	m_vScale = { 0.3f, 0.3f ,0.3f };
	m_vSize = { FBOX_XSIZE, FBOX_YSIZE, FBOX_ZSIZE };
	m_iHndl = -1;
	isAllive = true;
}

void CFootBox::Init(VECTOR vPos, VECTOR vScale, VECTOR vRot)
{
	for (int i = 0; i < FBOX_MAX_NUM; i++) {
		m_vPos = vPos;
		m_vScale = vScale;
		m_vRot = vRot;
	}
}

void CFootBox::Load()
{
	m_iHndl = MV1LoadModel(FBOX_PATH);
}

void CFootBox::Step() {
	if (CInput::IsKeyPush(KEY_INPUT_0)) {
		isAllive = false;
	}
}

void CFootBox::Draw()
{
	if (isAllive) {
		MV1DrawModel(m_iHndl);
	}
}

void CFootBox::Update()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1SetPosition(m_iHndl, m_vPos);
}

VECTOR CFootBox::GetHalfSize()
{
	VECTOR vHalfSize;

	return vHalfSize = DivVec(m_vSize, 2.0f);
}
