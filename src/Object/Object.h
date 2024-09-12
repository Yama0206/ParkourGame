#pragma once
#include "DxLib.h"

class CObject
{
protected:
	VECTOR m_vPos;		//座標
	VECTOR m_vRot;		//回転値
	VECTOR m_vSize;		//縦　横　奥行きのサイズ
	VECTOR m_vScale;	//拡縮率

	int m_iHndl;		//画像ハンドル
	bool m_IsAllive;	//生存フラグ


public:
	//初期化
	void Init();
	//読み込み
	void Load(int iMdHndl);
	//通常処理
	void Step();
	//描画
	void Draw();
	//終了処理
	void Fin();
	//更新処理
	void Update();

public:
	//情報を入れる
	void SetInfo(VECTOR vPos, VECTOR vSize, VECTOR vRot);

};
