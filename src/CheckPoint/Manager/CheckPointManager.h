#pragma once
#include "DxLib.h"
#include "../CheckPoint.h"
#include "../ReadList/ReadCheckPointList.h"
#include "../../Debug/DebugManager.h"
#include <vector>

using namespace std;

constexpr int PLAYER_PASSED_LIST_SIZE = 20;				//プレイヤーが通った場所を保存しておくリストのサイズ

class CCheckPointManager
{
private:
	static CCheckPointManager* m_Instance;

private:
	//ベースクラス
	vector <CCheckPoint*> m_cCheckPointList;			//チェックポイント
	//情報を入れるリストクラス
	CReadCheckPointList m_cFileDataList;				//チェックポイントの情報を入れるリスト

	int m_iPassedPlayerNum[PLAYER_PASSED_LIST_SIZE];	//プレイヤーが通った場所

	int m_iLastPassedPlayerNum;							//プレイヤーが最後に通った場所

	int m_iLastPassedEnemyNum;							//敵が最後に通った場所

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
	void Step();

	//クラスのサイズ取得
	inline int	GetSize() { return m_cCheckPointList.size(); }

	//取得関数
	//　iID : チェックポイントの番号
	VECTOR	GetPosVec				(int iID)					{ return m_cCheckPointList[iID]->GetPosVec(); }							//座標
	float	GetRad					(int iID)					{ return m_cCheckPointList[iID]->GetRad(); }							//半径
	int		GetArrayIndex			(int iID)					{ return m_cCheckPointList[iID]->GetArrayIndex(); }						//チェックポイントの次の場所の数
	int		GetNextCurrentNum		(int iID, int CurrentIndex)	{ return m_cCheckPointList[iID]->GetNextCurrentNum(CurrentIndex); }		//次に向かうチェックポイントの番号
	int		GetPassedPlayerNum		(int iID)					{ return m_iPassedPlayerNum[iID]; }										//プレイヤーが通った場所の番号(添え字の番号を返す)
	int		GetPassedPlayerNum		();																									//プレイヤーが通った場所の番号
	int		GetPassedPlayerNumSize	();
	int		GetLastPassedPlayerNum	()							{ return m_iLastPassedPlayerNum; }										//プレイヤーが最後に通った番号
	int		GetLastPassedEnemyNum	()							{ return m_iLastPassedEnemyNum; }										//敵が最後に通った番号

	//設定関数
	//　iID : チェックポイントの番号
	void	SetPosVec				(int iID, VECTOR vPos)		{  m_cCheckPointList[iID]->SetPosVec(vPos); }							//座標
	void	SetRad					(int iID, float fRad)		{  m_cCheckPointList[iID]->SetRad(fRad); }								//半径
	void	SetPassedPlayerNum		(int iNum);																							//プレイヤーが通った番号
	void	InitPassedPlayerNum		(int iID)					 { m_iPassedPlayerNum[iID] = -1; }										//プレイヤーが通った番号の配列を添え字の番号の部分を初期化する
	void	SetLastPassedPlayerNum	(int iNum)					{ m_iLastPassedPlayerNum = iNum; }										//プレイヤーが最後に通った番号
	void	SetLastPassedEnemyNum	(int iNum)					{ m_iLastPassedEnemyNum = iNum; }										//敵が最後に通った番号

	//プレイヤーが通った場所の配列を削除
	void	ClearPassedPlayerNum();																									//プレイヤーが通った番号
};