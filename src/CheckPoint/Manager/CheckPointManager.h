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

	eCP_Num m_eCP_Num;		//チェックポイント番号

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
	int GetCheckPointSize() { return m_cCheckPointList.size(); }
	bool GetIsArrive(int iID) { return m_cCheckPointList[iID]->GetIsArrived(); }
	void SetIsAriive(int iID, bool IsFrag) {  m_cCheckPointList[iID]->SetIsArrived(IsFrag); }

	eCP_Num GetCPNum() { return m_cCheckPointList[m_eCP_Num]->GetCPNum(); }									//チェックポイント番号の取得
	void SetCPNum(eCP_Num Num) { m_cCheckPointList[m_eCP_Num]->SetCPNum(Num); }								//チェックポイント番号の設定
	void AddCPNum();

	//座標取得
	VECTOR GetPosVec(int iID) { return m_cCheckPointList[iID]->GetPosVec(); }

};