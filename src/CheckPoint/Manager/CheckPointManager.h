#pragma once
#include "DxLib.h"
#include "../CheckPoint.h"
#include "../ReadList/ReadCheckPointList.h"
#include <vector>

using namespace std;


class CCheckPointManager
{
private:
	static CCheckPointManager* m_Instance;

private:
	//ベースクラス
	vector <CCheckPoint*> m_cCheckPointList;			//チェックポイント
	//情報を入れるリストクラス
	CReadCheckPointList m_cFileDataList;				//チェックポイントの情報を入れるリスト

	vector<int> m_iPassedPlayerNum;						//プレイヤーが通った場所

public:
	//シングルトンのクラス取得と破棄--------------
	//CCheckPointManagerを取得
	static CCheckPointManager* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();
	//--------------------------------------------

public:
	CCheckPointManager();						//コンストラクタ
	~CCheckPointManager();						//デストラクタ

	//読み込み
	void Load();

	//クラスのサイズ取得
	inline int	GetSize() { return m_cCheckPointList.size(); }

	//取得関数
	//　iID : チェックポイントの番号
	VECTOR	GetPosVec			(int iID)					{ return m_cCheckPointList[iID]->GetPosVec(); }							//座標
	float	GetRad				(int iID)					{ return m_cCheckPointList[iID]->GetRad(); }							//半径
	bool	GetIsPassedPlayer	(int iID)					{ return m_cCheckPointList[iID]->GetPassedPlayer(); }					//プレイヤーが通ったかどうか
	int		GetArrayIndex		(int iID)					{ return m_cCheckPointList[iID]->GetArrayIndex(); }						//チェックポイントの次の場所の数
	int		GetNextCurrentNum	(int iID, int CurrentIndex)	{ return m_cCheckPointList[iID]->GetNextCurrentNum(CurrentIndex); }		//次に向かうチェックポイントの番号
	int		GetPassedPlayerNum	(int iID)					{ return m_iPassedPlayerNum[iID]; }										//プレイヤーが通った場所の番号
	int		GetPassedPlayerNum	()							{ return m_iPassedPlayerNum.back(); }									//プレイヤーが通った場所の番号
	int		GetPassedPlayerSize	()							{ return m_iPassedPlayerNum.size(); }									//プレイヤーが通った場所サイズ

	//設定関数
	//　iID : チェックポイントの番号
	void	SetPosVec			(int iID, VECTOR vPos)		{  m_cCheckPointList[iID]->SetPosVec(vPos); }					//座標
	void	SetRad				(int iID, float fRad)		{  m_cCheckPointList[iID]->SetRad(fRad); }						//半径
	void	SetIsPassedPlayer	(int iID, bool IsFrag)		{ m_cCheckPointList[iID]->SetPassedPlayer(IsFrag); }			//プレイヤーが通ったかどうか
	void	SetPassedPlayerNum	(int Num)					{ m_iPassedPlayerNum.push_back(Num); }							//プレイヤーが通った場所の番号

	//プレイヤーが通った場所の配列を削除
	void	ClearPassedPlayerNum()							{ m_iPassedPlayerNum.clear(); }									//プレイヤーが通った場所の番号
};