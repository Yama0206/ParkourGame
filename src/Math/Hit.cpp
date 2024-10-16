#include "Hit.h"


//2D
//IsHitRectの定義
bool CHit::IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		// 当たっているときの処理
		return true;
	}
	return false;
}

//IsHitCircleの定義
bool CHit::IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//当たっている時の処理
		return true;
	}

	return false;

}

//3D
//直方体当たり判定
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
		//当たっている時の処理
		return true;
	}

	//当たっていないとき
	return false;
}

//球の当たり判定
bool CHit::IsHitSphere(VECTOR aPos, float aR, VECTOR bPos, float bR)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) +
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - bPos.z) * (aPos.z - bPos.z))
	{
		//当たっているとき
		return true;
	}
	//あたっていないとき
	return false;
}

