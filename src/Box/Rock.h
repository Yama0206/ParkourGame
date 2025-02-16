#pragma once
#include "FootBox.h"
#include "DxLib.h"

//定義
const float ROCK_X_SIZE = 140.0f;
const float ROCK_Y_SIZE = 5.0f;
const float ROCK_Z_SIZE = 120.0f;

class CRock : public CFootBox
{
private:

public:
	void Init();					//初期化
	void Init(VECTOR vPos, VECTOR vScale);			//初期座標
	void Load();					//読み込み	
	void Step();					//通常処理
	void Draw();					//描画
	void Fin();						//終了処理
};
