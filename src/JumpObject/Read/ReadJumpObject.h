#pragma once
#include "../../Read/Read.h"

using namespace std;

class CReadJumpObjectManager
{
private:
	struct SJumpObject
	{
		VECTOR m_vPos;		//座標
		VECTOR m_vRot;		//回転値
		VECTOR m_vSize;		//大きさ
		VECTOR m_vScale;	//拡縮率

		bool m_IsAllive;	//生存フラグ
	};

	SJumpObject m_sItemData;		//アイテムの情報が入った構造体

public:
	//アイテムの情報を入れるリスト
	vector<SJumpObject> jumpobjectList;

	//アイテム情報を読み込み
	void ReadFile();

};