#pragma once
#include "DxLib.h"
#include "../Collision/Collision.h"

static class CHit
{
public:
	//2D関数

	//点と矩形の当たり判定
	//vDotPos		:	点の位置
	//vSquarePos	:	矩形の中心位置
	//vSize			:	矩形の縦、横幅(半径)


//2Dの当たり判定
//四角形の当たり判定
//IsHitRectのプロトタイプ宣言
	static bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
	//3Dの当たり判定
	//第一引数,オブジェクト1の座標、第二引数,オブジェクト1の幅・高さ・奥行き
	//第三引数,オブジェクト2の座標、第四引数,オブジェクト2の幅・高さ・奥行き
	static bool IsHitRect(VECTOR ACenterPos, VECTOR AHalfSize, VECTOR BCenterPos, VECTOR BHalfSize);


	//円の当たり判定
	//IsHitCircleのプロトタイプ宣言
	static bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR);
	//球の当たり判定
	//第一引数、球1の半径、第二引数、球1の座標
	//第三引数、球2の半径、第四引数、球2の座標
	static bool IsHiSphere( VECTOR aPos, float aR, VECTOR bPos, float bR);
};
