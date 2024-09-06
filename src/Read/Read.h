#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>

const int  MAP_CHIP_X_NUM = 10;		//マップチップ横の数
const int  MAP_CHIP_Y_NUM = 1;		//マップチップ縦の数

const int TYPE_NUM = 256;					//テストタイプの配列の数
const int PATH_NUM = 256;					//テストパスの配列の数


enum Type
{
	a = 1,
	b, 
	c,
	d,
};

struct s_List
{
	VECTOR m_vPos;
	VECTOR m_vSize;

	char m_cType[TYPE_NUM];
	char m_cPath[PATH_NUM];
};



class CRead
{
private:
	s_List m_Test;
	Type eType;

	int mapIndex;			//読み込むオブジェクトの構造体の配列の番号

	//マップチップが格納された変数
	int m_FileReadMapData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];

public:
	//初期化
	void Init();

	//ファイル読み込み
	void ReadFile();
	//ファイルの書きこみ
	void SaveFile();

	//デバッグ用描画
	void Draw();

	//csvの値を取得
	int GetFileReadMapData(int x_index, int y_index) { return m_FileReadMapData[y_index][x_index]; }


};
