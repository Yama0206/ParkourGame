#include "Rock.h"

const char ROCK_PATH[] = { "data/Box/Rock.mv1" };

void CRock::Init()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vScale, 1.0f, sizeof(VECTOR));
	memset(&m_vRot, 0.0f, sizeof(VECTOR));
	m_vSize = { ROCK_X_SIZE , ROCK_Y_SIZE, ROCK_Z_SIZE };
	m_iHndl = -1;
	isAllive = true;
}

void CRock::Init(VECTOR vPos, VECTOR vScale)
{
	m_vPos = vPos;
	m_vScale = vScale;
}

void CRock::Load()
{
	if (m_iHndl == -1) {
		m_iHndl = MV1LoadModel(ROCK_PATH);
	}
}

void CRock::Step()
{

}

void CRock::Draw()
{
	MV1DrawModel(m_iHndl);
}

void CRock::Fin()
{
	//“Á‚É‚È‚µ
}