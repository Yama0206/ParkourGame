#pragma once
#include "DxLib.h"
#include "Enemy.h"
#include "Enemy_2.h"
#include "../Read/EnemyList/EnemyList.h"

#define ENEMY_NUM		(50)

class CEnemyManager
{
private:
	//敵、敵のタイプが増えるとここのクラスも増えていく
	//本当はメモリの動的確保が望ましい
	CEnemy m_cEnemy[ENEMY_NUM];
	
	//敵情報を読み込むためのクラス
	CEnemyRead m_cEnemyRead;


	int m_iWaitCnt;		//敵が生成されるまでの時間
	int m_iWaitCnt_2;	//2体目の敵が生成されるまでの時間	

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
	void Step();
	//描画処理
	void Draw();

	//敵情報取得
	inline CEnemy& GetEnemy(int iID) { return m_cEnemy[iID]; }

	//敵リクエスト
	void RequestEnemy();

};

