#include "Hit.h"


//2D
//IsHitRect‚Ì’è‹`
bool CHit::IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		// “–‚½‚Á‚Ä‚¢‚é‚Æ‚«‚Ìˆ—
		return true;
	}
	return false;
}

//IsHitCircle‚Ì’è‹`
bool CHit::IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//“–‚½‚Á‚Ä‚¢‚é‚Ìˆ—
		return true;
	}

	return false;

}

//3D
//’¼•û‘Ì“–‚½‚è”»’è
bool CHit::IsHitRect(VECTOR ACenterPos, VECTOR ASize, VECTOR BCenterPos, VECTOR BSize)
{
	VECTOR AHalfSize = VScale(ASize, 0.5);
	VECTOR BHalfSize = VScale(BSize, 0.5);


	if (BCenterPos.x - BHalfSize.x < ACenterPos.x + AHalfSize.x &&
		BCenterPos.x + BHalfSize.x > ACenterPos.x - AHalfSize.x &&
		BCenterPos.y + BHalfSize.y > ACenterPos.y - AHalfSize.y &&
		BCenterPos.y - BHalfSize.y < ACenterPos.y + AHalfSize.y &&
		BCenterPos.z + BHalfSize.z > ACenterPos.z - AHalfSize.z &&
		BCenterPos.z - BHalfSize.z < ACenterPos.z + AHalfSize.z)
	{
		//“–‚½‚Á‚Ä‚¢‚é‚Ìˆ—
		return true;
	}

	//“–‚½‚Á‚Ä‚¢‚È‚¢‚Æ‚«
	return false;
}

//‹…‚Ì“–‚½‚è”»’è
bool CHit::IsHitSphere(VECTOR aPos, float aR, VECTOR bPos, float bR)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) +
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - bPos.z) * (aPos.z - bPos.z))
	{
		//“–‚½‚Á‚Ä‚¢‚é‚Æ‚«
		return true;
	}
	//‚ ‚½‚Á‚Ä‚¢‚È‚¢‚Æ‚«
	return false;
}

