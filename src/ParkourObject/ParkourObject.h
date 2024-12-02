#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

enum ParkourType
{
	
};

class ParkourObject : public CObject
{
private:


public:
	//î•ñ‚Ìİ’è
	void SetInfo(VECTOR vPos, VECTOR vSize, bool bIsAllive);

	//æ“¾
	VECTOR GetPosVec()		{ return m_vPos; }			//À•W
	VECTOR GetSizeVec()		{ return m_vSize; }			//‘å‚«‚³

};