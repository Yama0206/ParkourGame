
#include "Collision.h"

//2D
//IsHitRectの定義
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
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
bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//当たっている時の処理
		return true;
	}

	return false;

}

bool IsHitRect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) {
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
bool IsHitCircle(float aX, float aY, float aR, float bX, float bY, float bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//当たっている時の処理
		return true;
	}

	return false;

}

//3D
//直方体当たり判定
bool IsHitRect(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
	if (bPos.x < aPos.x + aSize.x &&
		bPos.x + bSize.x > aPos.x &&
		bPos.y + bSize.y > aPos.y &&
		bPos.y < aPos.y + aSize.y &&
		bPos.z + bSize.z > aPos.z &&
		bPos.z < aPos.z + aSize.z)
	{
		//当たっている時の処理
		return true;
	}

	//当たっていないとき
	return false;
}

//球の当たり判定
bool SphereCollision(float aR, VECTOR aPos, float bR, VECTOR bPos)
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