#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

enum ParkourType
{
	TYPE_1,			//タイプ1


};

class CParkourObject : public CObject
{
private:


public:
	void Load(int iModelHndl);

public:
	//情報の設定
	void SetInfo(VECTOR vPos, VECTOR vScale, bool bIsAllive);

	//取得
	VECTOR GetPosVec()		{ return m_vPos; }			//座標
	VECTOR GetSizeVec()		{ return m_vSize; }			//大きさ


	void Update();

};