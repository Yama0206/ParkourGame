#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include "../Coin/Coin.h"
#include "../../Object/ObjectManager.h"
#include "../../Read/ItemList/ItemList.h"

using namespace std;

class CItemManager : public CObjectManager
{
private:
	//種類が増えるとここのクラスも増える
	vector<CCoin> m_cCoin;
	//アイテムの情報を読み込むためのクラス
	CItemList m_cItemList;

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
