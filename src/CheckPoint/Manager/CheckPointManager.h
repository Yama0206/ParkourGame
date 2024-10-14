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

	//プレイヤーが通ったチェックポイントの配列
	vector<int> m_ViaPlayer;

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

	//クラス取得
	inline CCheckPoint* GetCheckPoint(int iID) { return m_cCheckPointList[iID]; }								//チェックポイントクラス取得(おそらくもう使わない)

	//	//チェックポイントリスト数を取得
	int		 GetCheckPointSize()					{ return m_cCheckPointList.size(); }						//チェックポイントクラスのサイズを取得
	bool	 GetIsArrive(int iID)				{ return m_cCheckPointList[iID]->GetIsArrived(); }				//到着したかどうかのフラグを取得
	void	 SetIsAriive(int iID, bool IsFrag)	{ m_cCheckPointList[iID]->SetIsArrived(IsFrag); }				//到着したかどうかのフラグの設定

	int		 GetiCPNum(int iID)					{ return m_cCheckPointList[iID]->GetiCPNum(); }					//次に向かう場所の番号を取得
	void	 AddCPNum(int iID)					{ m_cCheckPointList[iID]->AddCPNum(); }							//チェックポイントの加算

	int		 GetNextNum(int Num, int iID)		{ return m_cCheckPointList[iID]->GetNextNum(Num); }				//次に向かうチェックポイントの番号

	//取得関数
	VECTOR	GetPosVec(int iID)				{ return m_cCheckPointList[iID]->GetPosVec(); }						//座標
	float	GetfRad(int iID)				{ return m_cCheckPointList[iID]->GetRad(); }						//回転値
	int		GetViaPlayer()					{ return m_ViaPlayer.back(); }										//プレイヤーが通った場所の番号の配列の末尾の要素を返す
	int		GetViaPlayerSize()				{ return m_ViaPlayer.size(); }										//プレイヤーが通った場所の番号の配列のサイズを返す

	//設定関数
	void	SetCPNum(int Num, int iID)		{ m_cCheckPointList[iID]->SetiCPNum(Num); }							//次に向かう場所の番号を設定
	void	SetViaPlayer(int iID);																				//プレイヤーが来た場所の番号を記憶
};