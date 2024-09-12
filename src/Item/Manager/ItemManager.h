#pragma once
#include "DxLib.h"
#include "../Coin/Coin.h"

class CItemManager
{
private:

public:
	CItemManager();		//コントラクタ
	~CItemManager();	//デストラクタ

public:
	//初期化
	void Init();
	//読み込み
	void Load();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();

};
