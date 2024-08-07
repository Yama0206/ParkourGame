#pragma once
#include "DxLib.h"
#include <vector>
#include "../Math/Math.h"
#include "../Input/Input.h"

using namespace std;

//íËêî
const char FBOX_PATH[] = { "data/Box/rocks.x" };
const float FBOX_XSIZE = 25.0f;
const float FBOX_YSIZE = 10.0f;
const float FBOX_ZSIZE = 25.0f;
const float FBOX_HALFSIZE = 0.0f;
//ë´èÍÇÃêî
const int FBOX_MAX_NUM = 16;

class CFootBox {
protected:
	VECTOR m_vPos;
	VECTOR m_vSize;
	VECTOR m_vRot;
	VECTOR m_vScale;
	int m_iHndl;
	bool isAllive;

public:
	void Init();
	void Init(VECTOR vPos, VECTOR vScale, VECTOR vRot);
	void Load();
	void Step();
	void Draw();
	void Update();

	VECTOR GetPotision(VECTOR& vPos) { return vPos = m_vPos; }
	VECTOR GetCenterPos(VECTOR& vPos, float UpValue) { return vPos = VGet(m_vPos.x, m_vPos.y + UpValue, m_vPos.z); }
	VECTOR GetSize() { return m_vSize; }
	VECTOR GetHalfSize();
	VECTOR GetRadius() { return DivVec(m_vSize, 2); }
};
