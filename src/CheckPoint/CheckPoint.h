#pragma once
#include "DxLib.h"

enum eCP_Num
{
	Point_1 = 1,		//ポイント1
	Point_2,			//ポイント2
	Point_3,			//ポイント3
	Point_4,			//ポイント4
	Point_5,			//ポイント5
};

class CCheckPoint
{
private:
	VECTOR m_vPos;		//座標
	VECTOR m_vSize;		//サイズ
	eCP_Num m_eCP_Num;	//チェックポイント番号

	float m_fRad;		//半径

	int m_iCPNum;		//チェックポイント番号

	//フラグ
	bool m_PlayerHit;		//プレイヤーが当たったかどうか
	bool m_IsArrived;		//到着した
public:
	CCheckPoint();		//コンストラクタ
	~CCheckPoint();		//デストラクタ

	void SetInfo(int Num, VECTOR vPos, VECTOR vSize, float fRad);

	//取得関数
	VECTOR	GetPosVec()		{ return m_vPos; }				//座標
	VECTOR* GetpPosVec()	{ return &m_vPos; }				//座標取得
	VECTOR	GetSizeVec()	{ return m_vSize; }				//サイズ
	float	GetRad()		{ return m_fRad; }				//半径
	int		GetiCPNum()		{ return m_iCPNum; }			//チェックポイントの番号
	bool	GetIsArrived()	{ return m_IsArrived; }			//到着したフラグ取得
	eCP_Num GetCPNum()		{ return m_eCP_Num; }			//チェックポイント番号の取得
	

	//設定関数
	void SetIsArrived(bool IsFrag)	{ m_IsArrived = IsFrag; }			//到着したフラグ
	void SetCPNum(eCP_Num Num)		{ m_eCP_Num = Num; }				//チェックポイント番号
	void SetiCPNum(int Num)			{ m_iCPNum = Num; }					//チェックポイントの番号

	//チェックポイント番号の加算
	void AddCPNum();

};
