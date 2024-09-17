#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include "../ItemBase/ItemBase.h"
#include "../Coin/Coin.h"
#include "../Test.h"
#include "../../Object/ObjectManager.h"
#include "../../Read/ReadItemList/ReadItemList.h"

using namespace std;

class CItemManager : public CObjectManager
{
private:
	//ポリフォーフィズム
	//ベースクラスをvector型で宣言
	vector<CItemBase *> m_cItemList;
<<<<<<< HEAD
=======
	//アイテムごとのクラス
	CCoin m_cCoin;
	Test m_test;
>>>>>>> f32ce091bef08de189faf64a129534c0d7275c2c
	//アイテムの情報を読み込むためのクラス
	CReadItemList m_cFileDataList;

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
