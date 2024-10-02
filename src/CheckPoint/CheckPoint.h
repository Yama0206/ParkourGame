#pragma once
#include "DxLib.h"

class CCheckPoint
{
private:
	VECTOR m_vPos;		//座標
	VECTOR m_vSize;		//サイズ

	float m_fRad;		//半径

	//フラグ
	bool m_PlayerHit;		//プレイヤーが当たったかどうか
public:
	CCheckPoint();		//コンストラクタ
	~CCheckPoint();		//デストラクタ

	void SetInfo(VECTOR vPos, VECTOR vSize, float fRad);

	//取得関数
	VECTOR GetPosVec() { return m_vPos; }					//座標
	VECTOR* GetpPosVec() { return &m_vPos; }		//座標取得
	VECTOR GetSizeVec() { return m_vSize; }					//サイズ
	float  GetRad() { return m_fRad; }						//半径


};
