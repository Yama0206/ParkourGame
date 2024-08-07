#pragma once
#include "DxLib.h"

//定義
const int TIME_IMAGE_NUM = 10;

struct STime {
	VECTOR m_vPos;
	VECTOR m_vScale;

	int m_iHndl[TIME_IMAGE_NUM];
};

class CUI
{
private:
	//構造体
	static STime m_sTime;		// 時間表示UI


public:
	//初期化
	static void Init();
	//読みこみ
	static void Load();
	//終了処理
	static void Exit();

	// 時間表示関数
	static void DrawTime();
};
