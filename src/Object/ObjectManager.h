#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

#include "../Read/ReadObjectList/ReadObjectList.h"


const int OBJECT_NUM = 50;

class CObjectManager
{
private:
	//オブジェクトが増えるとここのクラスも増える
	CObject m_cObject[OBJECT_NUM];

	//オブジェクト情報を読み込むためのクラス
	CObjectRead m_cObjectRead;

public:
	//コンストラクタ・デストラクタ
	CObjectManager();
	~CObjectManager();

	//初期化
	void Init();
	//初期値設定
	void InitValue();
	//データロード
	void Load();
	//終了処理
	void Fin();
	//繰り返し行う処理
	void Step();
	//描画処理
	void Draw();
	//更新処理
	void Update();

};