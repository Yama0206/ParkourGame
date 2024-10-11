#pragma once
#include "DxLib.h"
#include <vector>

using namespace std;

class CCheckPoint
{
private:
	VECTOR m_vPos;					//座標
	VECTOR m_vSize;					//サイズ

	float m_fRad;					//半径

	int m_iCPNum;					//チェックポイント番号
	int m_NextCPNum[4];				//次に向かうチェックポイントの番号
	vector<int> m_ViaPlayer;		//プレイヤーが通ったチェックポイントの配列

	//フラグ
	bool m_PlayerHit;				//プレイヤーが当たったかどうか
	bool m_IsArrived;				//到着した
	bool m_IsPassedPlayer;			//プレイヤーが通った

public:
	CCheckPoint();					//コンストラクタ
	~CCheckPoint();					//デストラクタ

	//	情報の設定
	void SetInfo(int Num, VECTOR vPos, VECTOR vSize, float fRad, int* NextCPNum);

	//取得関数
	VECTOR	GetPosVec()					{ return m_vPos; }				//座標
	VECTOR* GetpPosVec()				{ return &m_vPos; }				//座標取得
	VECTOR	GetSizeVec()				{ return m_vSize; }				//サイズ
	float	GetRad()					{ return m_fRad; }				//半径
	int		GetiCPNum()					{ return m_iCPNum; }			//チェックポイントの番号
	bool	GetIsArrived()				{ return m_IsArrived; }			//到着したフラグ取得
	int		GetNextNum(int iID)			{ return m_NextCPNum[iID]; }	//次に向かうチェックポイントの番号
	bool	GetSetPassedPlayer()		{ return m_IsPassedPlayer; }	//プレイヤーが通ったかのフラグ
	int		GetViaPlayer(int iID);										//プレイヤーが通った場所の変数
		

	//設定関数
	void SetIsArrived(bool IsFrag)		{ m_IsArrived = IsFrag; }			//到着したフラグ
	void SetiCPNum(int Num)				{ m_iCPNum = Num; }					//チェックポイントの番号
	void SetPassedPlayer(bool IsFrag)	{ m_IsPassedPlayer = IsFrag; }		//プレイヤーが通ったかどうかのフラグ

	//チェックポイント番号の加算
	void AddCPNum();

};
