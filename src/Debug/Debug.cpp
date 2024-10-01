#include "Debug.h"

void CDebug::PrintPos(int posX, int posY, VECTOR vPos)
{
	DrawFormatString(posX, posY, GetColor(255, 0, 0), "%f, %f, %f", vPos.x, vPos.y, vPos.z);
}

void CDebug::PrintSpeed(int posX, int posY, float fSpeed)
{
	DrawFormatString(posX, posY, GetColor(255, 0, 0), "%f", fSpeed);
}

void CDebug::PrintRot(int posX, int posY, float fRot)
{
	DrawFormatString(posX, posY, GetColor(255, 0, 0), "%f", fRot);
}