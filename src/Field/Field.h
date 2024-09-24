#pragma once
#include "DxLib.h"

const char FIELD_PATH[] = { "data/field/KariMap.mv1" };
const float FIELD_X_SIZE = 500.0f;								//Xサイズ
const float FIELD_Y_SIZE = 0.0f;								//Yサイズ
const float FIELD_Z_SIZE = 500.0f;								//Zサイズ
const float FIELD_X_SCALE = 0.5f;								//Xの拡大縮小率
const float FIELD_Y_SCALE = 0.5f;								//Yの拡大縮小率
const float FIELD_Z_SCALE = 0.5f;								//Zの拡大縮小率

class CField
{
protected:
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//サイズ
	VECTOR m_vScale;		//拡縮率

	int m_iHndl;			//画像ハンドル
	bool m_IsHitFrag;		//当たったかどうか

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


	//更新処理
	VECTOR HitCheck(VECTOR vCenter, float fRadius);

	//フィールドの座標取得
	VECTOR GetPos() { return m_vPos; }

	//フィールドのサイズ取得
	VECTOR GetSize() { return m_vSize; }
};
