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
	//敵情報取得
	inline CEnemy* GetEnemy(int iID) { return m_cEnemyList[iID]; }
	//クラスのサイズ取得
	int GetEnemySize() { return m_cEnemyList.size(); }

	//取得関数
	//VECTOR	GetPosVec(int iID)				{ return m_cEnemyList[iID]->GetPosVec(); }									//座標
	//VECTOR	GetSpeedVec(int iID)			{ return m_cEnemyList[iID]->GetSpeedVec(); }								//速さ
	//int		GetPassedCheckPoint(int iID)	{ return m_cEnemyList[iID]->GetLastPassedCheckPoint(); }					//最後に通ったチェックポイント

	//設定関数
	//void	SetPosVec(VECTOR vPos, int iID)				{ return m_cEnemyList[iID]->SetPosVec(vPos); }					//座標
	//void	SetSpeedVec(VECTOR vSpeed, int iID)			{ return m_cEnemyList[iID]->SetSpeedVec(vSpeed); }				//速さ
	//void	SetPassedCheckPoint(int Num, int iID)		{ return m_cEnemyList[iID]->SetLastPassedCheckPoint(Num); }		//最後に通ったチェックポイント

	//敵リクエスト
	void RequestEnemy();

};

