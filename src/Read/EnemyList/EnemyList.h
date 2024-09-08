#pragma once
#include "../Read.h"

//定義
const char ENEMY_TXT_PATH[] = { "data/File/Enemy.txt" };		//敵情報のテキストファイルパス
const int  ENEMY_STRUCT_NUM = 5;								//敵構造体の配列の数

struct SEnemy
{
	VECTOR m_vPos;			//座標
	VECTOR m_vSize;			//拡大縮小率
	VECTOR m_vRot;			//回転値

	Type m_eType;			//種類

	int m_iHndl;			//画像ハンドル
};

class CEnemyRead : public CRead
{
private:
	SEnemy m_sEnemy[ENEMY_STRUCT_NUM];		//敵の情報構造体

public:
	void ReadFile();														//ファイル読み込み

	SEnemy GetStructEnemy(SEnemy& Enemy) { return Enemy; }		//敵情報の構造体を取得

};
