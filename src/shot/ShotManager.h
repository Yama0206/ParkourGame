#pragma once
#include "Shot.h"
#include "../System/Sound/SoundManager.h"

#define PL_SHOT_NUM (50)

class CShotManager
{
private:
	//プレイヤーのショット
	//本当はメモリの動的確保が望ましい
	CShot cPlayerShot[PL_SHOT_NUM];

public:
	//コンストラクタ・デストラクタ
	CShotManager();
	~CShotManager();

	//初期化
	void Init();
	//データロード
	void Load();
	//終了処理
	void Fin();
	//繰り返し行う処理
	void Step();
	//描画処理
	void Draw();

	//プレイヤーのショットリクエスト
	void RequestPlayerShot(const VECTOR &vPos, const VECTOR &vSpeed);
	//プレイヤーのショット情報取得
	CShot& GetPlayerShot(int iID) { return cPlayerShot[iID]; }

	
};
