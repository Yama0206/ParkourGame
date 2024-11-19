#pragma once
#include "../Read.h"


using namespace std;

//定義
const char OBJECT_TXT_PATH[] = { "data/File/Object/Object.txt" };

struct SObject
{
	VECTOR m_vPos;		//座標
	VECTOR m_vSize;		//拡縮率
	VECTOR m_vRot;		//回転値

	ReadType m_eType;		//種類
};

class CObjectRead : public CRead
{
private:
	//オブジェクト情報を格納する構造体
	SObject m_sObject;

public:
	//読み込みデータリスト
	vector<SObject> objectInfoList;

	void ReadFile();
};
