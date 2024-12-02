#pragma once
#include "../../Read/Read.h"
#include "../../ParkourObject/ParkourObject.h"



struct SParkourObject
{
	VECTOR m_vPos;		//座標
	VECTOR m_vSize;		//大きさ

	bool IsAllive;		//生存フラグ
};

class ReadParkourObjectList : public CRead {

private:


public:
	//ファイル読み込み
	void ReadFile();

};
