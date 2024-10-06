#pragma once
#include "DxLib.h"
#include "../../Read/Read.h"
#include "../CheckPoint.h"
#include <vector>

using namespace std;


struct SCheckPoint
{
	VECTOR m_vPos;		//座標
	VECTOR m_vSize;		//サイズ
	eCP_Num m_eCP_Num;	//チェックポイントの番号

	float fRad;			//半径
	int m_iCPNum;		//チェックポイント番号
};


class CReadCheckPointList
{
private:
	//チェックポイントの情報が入った構造体
	SCheckPoint m_CheckPointData;
public:
	//チェックポイントの情報を入れる
	vector <SCheckPoint> checkPointList;

	//データへの読み込み
	void ReadFile();
};