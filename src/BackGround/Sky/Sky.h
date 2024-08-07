#pragma once
#include "DxLib.h"
#include "../BackGround.h"

const char SKY_IMG_PATH[] = { "data/Sky/Sky.x" };

class CSky
{
private:
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//サイズ
	VECTOR m_vScale;		//拡縮率
	VECTOR m_vRot;			//回転値

	int m_ImgHndl;			//画像ハンドル
public:

	void Init();

	//読み込み
	void Load();

	//通常処理
	void Step(); 

	//描画処理
	void Draw();

	//更新処理
	void UpDate();

	//終了処理
	void Fin();
};
