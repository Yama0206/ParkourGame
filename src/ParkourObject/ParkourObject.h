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
	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vSize, bool bIsAllive);

	//�擾
	VECTOR GetPosVec()		{ return m_vPos; }			//���W
	VECTOR GetSizeVec()		{ return m_vSize; }			//�傫��

};