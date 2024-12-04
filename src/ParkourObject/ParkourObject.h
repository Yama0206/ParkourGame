#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

enum ParkourType
{
	FENCE,			//フェンス


};

class CParkourObject : public CObject
{
protected:
	VECTOR m_vObjectPos;		//オブジェクト座標
	VECTOR m_vFrontPos;			//前側座標
	VECTOR m_vBackPos;			//後ろ座標
	VECTOR m_vRightPos;			//右側座標
	VECTOR m_vLeftPos;			//左側座標

	VECTOR m_vFrontSize;		//前側大きさ
	VECTOR m_vBackSize;			//後ろ大きさ
	VECTOR m_vRightSize;		//右側大きさ
	VECTOR m_vLeftSize;			//左側大きさ

public:
	void Load(int iModelHndl);

public:
	//情報の設定
	void SetInfo(VECTOR vObjectPos, VECTOR vFrontPos, VECTOR vBackPos, VECTOR vRightPos, VECTOR vLeftPos, bool bIsAllive);

	//取得
	VECTOR GetPosVec()		{ return m_vPos; }			//座標
	VECTOR GetSizeVec()		{ return m_vSize; }			//大きさ


	//更新処理
	void Update();

};