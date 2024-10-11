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

public:
	//CCheckPointManagerを取得
	static CCheckPointManager* GetInstance();

	//CCheckPointManagerを削除
	static void DeleteInstance();

public:
	CCheckPointManager();
	~CCheckPointManager();

	//読み込み
	void Load();

	//クラス取得
	inline CCheckPoint* GetCheckPoint(int iID) { return m_cCheckPointList[iID]; }

	//	//チェックポイントリスト数を取得
	int GetCheckPointSize()					{ return m_cCheckPointList.size(); }
	bool GetIsArrive(int iID)				{ return m_cCheckPointList[iID]->GetIsArrived(); }
	void SetIsAriive(int iID, bool IsFrag)	{  m_cCheckPointList[iID]->SetIsArrived(IsFrag); }

	int GetiCPNum(int iID)			{ return m_cCheckPointList[iID]->GetiCPNum(); }
	void SetCPNum(int Num, int iID)			{ m_cCheckPointList[iID]->SetiCPNum(Num); }
	void AddCPNum(int iID)			{ m_cCheckPointList[iID]->AddCPNum(); }										//チェックポイントの加算

	int GetNextNum(int Num, int iID) { return m_cCheckPointList[iID]->GetNextNum(Num); }						//次に向かうチェックポイントの番号

	//取得関数
	VECTOR	GetPosVec(int iID)	{ return m_cCheckPointList[iID]->GetPosVec(); }				//座標
	float	GetfRad(int iID)		{ return m_cCheckPointList[iID]->GetRad(); }				//回転値

	//設定関数
};