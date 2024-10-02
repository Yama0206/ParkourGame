#pragma once
#include "DxLib.h"
#include "../CheckPoint.h"
#include "../ReadList/ReadCheckPointList.h"
#include <vector>

using namespace std;

class CCheckPointManager
{
private:
	//ベースクラス
	vector <CCheckPoint*> m_cCheckPointList;			//チェックポイント
	//情報を入れるリストクラス
	CReadCheckPointList m_cFileDataList;		//チェックポイントの情報を入れるリスト

public:
	CCheckPointManager();
	~CCheckPointManager();

	//読み込み
	void Load();

	//クラス取得
	inline CCheckPoint* GetCheckPoint(int iID) { return m_cCheckPointList[iID]; }

	//	//チェックポイントリスト数を取得
	int GetCheckPointSize() { return m_cCheckPointList.size(); }
};