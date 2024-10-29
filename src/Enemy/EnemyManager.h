#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Boss/NormalBoss.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include "../Read/ReadEnemyList/ReadEnemyList.h"
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
	//プレイヤーを追跡する
	void TrackingPlayer(VECTOR vPlayerPos, int Index);
	//チェックポイントに移動する
	void TrackingCheckPoint(int Index);
	//プレイヤーが通ったチェックポイント
	void TrackingPassedPlayerPoint(int EnemyIndex, int CheckPointIndex);
	//敵が最後に通ったチェックポイントに向かう
	void TrackingPassedEnemyPoint(int Index);

	//敵情報取得
	inline CEnemy* GetEnemy(int iID) { return m_cEnemyList[iID]; }

	int GetEnemySize() { return m_cEnemyList.size(); }

	VECTOR GetPosVec(int iID) { return m_cEnemyList[iID]->GetPosVec(); }
	VECTOR GetSpeedVec(int iID) { return m_cEnemyList[iID]->GetSpeedVec(); }

	//敵リクエスト
	void RequestEnemy();

};

