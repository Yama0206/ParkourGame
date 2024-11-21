#pragma once
#include "DxLib.h"
#include <vector>

using namespace std;

//定義
constexpr int NEXT_CHECKPOINT_NUM = 4;													//次に向かうチェックポイントを記憶する変数の配列の最大数

class CCheckPoint
{
private:
	VECTOR m_vPos;																		//座標
	VECTOR m_vSize;																		//サイズ

	float m_fRad;																		//半径

	int m_iCurrentNum;																	//チェックポイント番号
	int m_NextCurrentNum[NEXT_CHECKPOINT_NUM];											//次に向かうチェックポイントの番号
	int m_iArrayIndex;																	//チェックポイントの次に迎える場所の数

public:
	CCheckPoint();																		//コンストラクタ
	~CCheckPoint();																		//デストラクタ

	//	情報の設定
	void SetInfo(int Num, VECTOR vPos, float fRad, int* NextCPNum);

	//取得関数
	VECTOR	GetPosVec()					{ return m_vPos; }											//座標
	VECTOR  GetSizeVec()				{ return m_vSize; }											//サイズ
	float	GetRad()					{ return m_fRad; }											//半径
	int		GetArrayIndex()				{ return m_iArrayIndex; }									//チェックポイントの次に迎える場所
	int		GetCurrentNum()				{ return m_iCurrentNum; }									//チェックポイントの番号
	int		GetNextCurrentNum(int iID)	{ return m_NextCurrentNum[iID]; }							//次に向かうチェックポイント

	//設定関数
	void SetPosVec			(VECTOR vPos)				{ m_vPos = vPos; }							//座標
	void SetRad				(float fRad)				{ m_fRad = fRad; }							//半径
	void SetNextCurrentNum(int CurrentNum, int iID)		{ m_NextCurrentNum[iID] = CurrentNum; }		//次に向かうチェックポイントの番号

	//チェックポイントの次に迎える場所の数を加算
	void AddArayIndex() { m_iArrayIndex++; }
};		
