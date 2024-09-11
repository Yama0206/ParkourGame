#pragma once
#include "DxLib.h"
#include "../Object/Object.h"
#include "../Read/ObjectList/ObjectList.h"

class CObjectManager
{
private:
	//オブジェクトが増えるとここのクラスも増える
	

	//オブジェクト情報を読み込むためのクラス


	//オブジェクト情報が入っている構造体

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

};