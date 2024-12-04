#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"
#include <vector>

using namespace std;

struct SParkourObject
{
	VECTOR m_vObjectPos;		//オブジェクト座標
	VECTOR m_vFrontPos;			//前側座標
	VECTOR m_vBackPos;			//後ろ座標
	VECTOR m_vRightPos;			//右側座標
	VECTOR m_vLeftPos;			//左側座標

	ParkourType m_eType;		//タイプ

	bool m_IsAllive;				//生存フラグ
};

class ReadParkourObjectList : public CRead {

private:
	SParkourObject m_sParkourData;

public:
	vector<SParkourObject> sparkourObjectInfoList;

	//ファイル読み込み
	void ReadFile();

};
