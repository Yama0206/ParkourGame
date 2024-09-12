#pragma once
#include "../Read.h"

using namespace std;

struct SCoin
{
	VECTOR m_vPos;		//座標
	VECTOR m_vRot;		//回転値
	VECTOR m_vScale;	//拡縮率

	Type m_eType;		//種類
};

class CItemList : public CRead
{
private:
	SCoin m_sItemData;		//アイテムの情報が入った構造体

public:
	vector<SCoin> itemInfoList;

	//アイテム情報を読み込み
	void ReadFile();
};
