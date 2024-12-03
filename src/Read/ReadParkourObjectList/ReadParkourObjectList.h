#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"
#include <vector>

using namespace std;

struct SParkourObject
{
	VECTOR m_vPos;				//座標
	VECTOR m_vScale;			//拡縮率
	ParkourType m_eType;		//タイプ

	bool IsAllive;		//生存フラグ
};

class ReadParkourObjectList : public CRead {

private:
	SParkourObject m_sParkourData;

public:
	vector<SParkourObject> sparkourObjectInfoList;

	//ファイル読み込み
	void ReadFile();

};
