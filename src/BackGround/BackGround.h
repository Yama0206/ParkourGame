#pragma once
#include "DxLib.h"

const char BACKGROUND_PATH[] = { "data/field/LavaField.mv1" };
const float BACKGROUND_X_SIZE = 500.0f;								//Xサイズ
const float BACKGROUND_Y_SIZE = 0.0f;								//Yサイズ
const float BACKGROUND_Z_SIZE = 500.0f;								//Zサイズ
const float BACKGROUND_X_SCALE = 0.5f;								//Xの拡大縮小率
const float BACKGROUND_Y_SCALE = 0.5f;								//Yの拡大縮小率
const float BACKGROUND_Z_SCALE = 0.5f;								//Zの拡大縮小率

class BackGround
{
protected:
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//サイズ
	VECTOR m_vScale;		//拡縮率
	int m_ImgHndl;			//画像ハンドル

public:
	//初期化
	void Init();

	//読み込み
	void Load();

	//通常処理
	void Step();

	//描画
	void Draw();

	//更新処理
	void UpDate();

	//終了処理
	void Fin();

	//フィールドの座標取得
	VECTOR GetPos() { return m_vPos; }

	//フィールドのサイズ取得
	VECTOR GetSize() { return m_vSize; }
};
