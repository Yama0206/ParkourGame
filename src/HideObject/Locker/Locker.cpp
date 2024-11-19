#include "Locker.h"

constexpr char LOCKER_PATH[] = { "data/Locker/Locker.x" };
constexpr int LOCKER_X_SIZE = 50;
constexpr int LOCKER_Y_SIZE = 50;
constexpr int LOCKER_Z_SIZE = 50;
constexpr float LOCKER_RADIUS = 50.0f;

void CLocker::Init()
{
	memset(&m_vPos, 0.0f, sizeof(m_vPos));
	memset(&m_vRot, 0.0f, sizeof(m_vRot));
	memset(&m_vSize, 0.0f, sizeof(m_vSize));
	memset(&m_vScale, 0.0f, sizeof(m_vScale));
	m_fRad = LOCKER_RADIUS;
	m_iHndl = -1;
	m_vScale = VGet(1.0f, 1.0f, 1.0f);
	m_vPos.y = 50.0f;
}

void CLocker::Load()
{
	m_iHndl = MV1LoadModel(LOCKER_PATH);

	
}

void CLocker::Draw()
{
	MV1DrawModel(m_iHndl);
}

void CLocker::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}