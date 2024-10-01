#pragma once

#include "DxLib.h"


class CDebug
{
private:
	

public:

	//座標描画
	// posX : 表示X座標
	// posY : 表示Y座標
	// vPos : 表示する座標
	void PrintPos(int posX, int posY, VECTOR vPos);

	//スピード描画
	// posX : 表示X座標
	// posY : 表示Y座標
	// fSpeed : 表示するスピード
	void PrintSpeed(int posX, int posY,float fSpeed);

	//回転値描画
	// posX : 表示X座標
	// posY : 表示Y座標
	// fRot : 表示する回転値
	void PrintRot(int posX, int posY, float fRot);

};
