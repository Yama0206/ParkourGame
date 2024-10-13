#pragma once
#include "../Read.h"
#include <iostream>
#include <vector>

using namespace std;

//定義
const char ENEMY_TXT_PATH[] = { "data/File/Enemy/Enemy.txt" };		//敵情報のテキストファイルパス

struct SEnemy
{
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//縦　横　奥ゆきサイズ
	VECTOR m_vRot;			//回転値
	VECTOR m_vSpeed;		//速さ
	VECTOR m_vScale;		//拡縮率
	bool m_IsActive;		//生存フラグ

	Type m_eType;			//種類
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemyData;		//敵の情報構造体

public:
	//読み込みデータリスト
	vector<SEnemy> enemyInfoList;

	//ファイル読み込み
	void ReadFile();			
};
