#pragma once
#include "../Read.h"

using namespace std;

//enum eType
//{
//	Coin = 1,
//	b, 
//	c,
//	d,
//};

struct SItem
{
	VECTOR m_vPos;		//座標
	VECTOR m_vRot;		//回転値
	VECTOR m_vSize;		//大きさ
	VECTOR m_vScale;	//拡縮率

	bool m_IsAllive;		//生存フラグ

	Type m_eType;		//種類
};

class CReadItemList : public CRead
{
private:
	SItem m_sItemData;		//アイテムの情報が入った構造体

public:
	//アイテムの情報を入れるリスト
	vector<SItem> itemInfoList;

	//アイテム情報を読み込み
	void ReadFile();
};
