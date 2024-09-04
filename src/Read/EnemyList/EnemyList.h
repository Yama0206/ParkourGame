#pragma once
#include "../Read.h"

//定義
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//敵情報のテキストファイルパス
const int  ENEMY_STRUCT_X_NUM = 5;								//敵構造体の配列の列数
const int  ENEMY_STRUCT_Y_NUM = 5;								//敵構造体の配列の行数


enum EEnemyType
{
	a = 1,
	b,
	c,
	d,
	e,

};

struct SEnemy
{
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//拡大縮小率
	VECTOR m_vRot;			//回転値

	EEnemyType m_eType;		//種類

	int m_iHndl;			//画像ハンドル
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemy[ENEMY_STRUCT_X_NUM][ENEMY_STRUCT_Y_NUM];		//敵の情報構造体

public:
	void ReadFile();												//ファイル読み込み
};
