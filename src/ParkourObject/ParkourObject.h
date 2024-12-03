#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

enum ParkourType
{
	TYPE_1,			//�^�C�v1


};

class CParkourObject : public CObject
{
private:


public:
	void Load(int iModelHndl);

public:
	//���̐ݒ�
	void SetInfo(VECTOR vPos, VECTOR vScale, bool bIsAllive);

	//�擾
	VECTOR GetPosVec()		{ return m_vPos; }			//���W
	VECTOR GetSizeVec()		{ return m_vSize; }			//�傫��


	void Update();

};