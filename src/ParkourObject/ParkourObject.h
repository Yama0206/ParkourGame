#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

enum ParkourType
{
	FENCE,			//�t�F���X


};

class CParkourObject : public CObject
{
protected:
	VECTOR m_vObjectPos;		//�I�u�W�F�N�g���W
	VECTOR m_vFrontPos;			//�O�����W
	VECTOR m_vBackPos;			//�����W
	VECTOR m_vRightPos;			//�E�����W
	VECTOR m_vLeftPos;			//�������W

	VECTOR m_vFrontSize;		//�O���傫��
	VECTOR m_vBackSize;			//���傫��
	VECTOR m_vRightSize;		//�E���傫��
	VECTOR m_vLeftSize;			//�����傫��

public:
	void Load(int iModelHndl);

public:
	//���̐ݒ�
	void SetInfo(VECTOR vObjectPos, VECTOR vFrontPos, VECTOR vBackPos, VECTOR vRightPos, VECTOR vLeftPos, bool bIsAllive);

	//�擾
	VECTOR GetPosVec()		{ return m_vPos; }			//���W
	VECTOR GetSizeVec()		{ return m_vSize; }			//�傫��


	//�X�V����
	void Update();

};