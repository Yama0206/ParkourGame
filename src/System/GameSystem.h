#pragma once
#include "DxLib.h"

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

};