#pragma once
#include "DxLib.h"

//定数
constexpr int STAGE1_COIN = 10;			//ステージ1コインの枚数
constexpr int STAGE2_COIN = 10;			//ステージ2コインの枚数
constexpr int STAGE3_COIN = 10;			//ステージ3コインの枚数

class CGameSystem 
{
private:
	//インスタンス
	static CGameSystem* m_Instance; 

	float m_fTimePosX;					//時間を表示するX座標
	float m_fTimePosY;					//時間を表示するY座標

	float m_fFreamPosX;					//フレームを表示するX座標
	float m_fFreamPosY;					//フレームを表示するY座標

	//メンバ変数
	int m_iFreamCnt;					//フレームカウント変数
	int m_iTimeCnt;						//時間カウント変数

	int m_PlayerLife;					//プレイヤーの残機

	int m_CoinNum;						//コイン取得枚数

	//フラグ
	bool m_IsClear;						//クリア条件を満たしたかどうか

public:

	//シングルトンのクラス取得と破棄--------------
//CCheckPointManagerを取得
	static CGameSystem* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();
	//--------------------------------------------

public:
	//読み込み
	void Load();
	//描画
	void Draw();

	//フレームをカウントする
	void CntFream();

	//時間をカウントする関数
	void CntTime();

	//コインの取得数をカウント
	void CntCoinNum() { m_CoinNum++; };

	//クリア判定
	void ClearDecision();

};