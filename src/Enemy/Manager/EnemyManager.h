#pragma once
#include "DxLib.h"
#include "../Enemy.h"
#include "../Boss/NormalBoss.h"
#include "../../CheckPoint/Manager/CheckPointManager.h"
#include "../../Read/ReadEnemyList/ReadEnemyList.h"
#include "../../Input/Input.h"
#include <iostream>
#include <vector>

using namespace std;

#define ENEMY_NUM		(50)


class CEnemyManager
{
private:
	//敵、敵のタイプが増えるとここのクラスも増えていく
	//本当はメモリの動的確保が望ましい
	vector<CEnemy*>m_cEnemyList;
	
	//敵情報を読み込むためのクラス
	CEnemyRead m_cEnemyRead;

	//サイズを保存する変数
	int EnemyGoSize;

	//プレイヤーがハイドモードか確認
	bool m_IsPlayerIsHideMode;

public:
	//コンストラクタ・デストラクタ
	CEnemyManager();
	~CEnemyManager();

	//初期化
	void Init();
	//初期値設定
	void InitValue();
	//データロード
	void Load();
	//終了処理
	void Fin();
	//繰り返し行う処理
	void Step(VECTOR vPlayerPos);
	//描画処理
	void Draw();
	//更新処理
	void Update();

public:
	//敵情報取得
	inline CEnemy* GetEnemy(int iID) { return m_cEnemyList[iID]; }
	//クラスのサイズ取得
	int GetEnemySize() { return (int)m_cEnemyList.size(); }

	//敵リクエスト
	void RequestEnemy();

public:
	//テレポート処理
	void Teleport(VECTOR vPos);

public:
	void SetIsPlayerHideMode(bool bflag) { m_IsPlayerIsHideMode = bflag; }
	bool GetIsPlayerHideMode() { return m_IsPlayerIsHideMode; }

};

