#pragma once
#include "DxLib.h"

class CCheckPoint
{
private:
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�T�C�Y

	float m_fRad;		//���a

	//�t���O
	bool m_PlayerHit;		//�v���C���[�������������ǂ���
public:
	CCheckPoint();		//�R���X�g���N�^
	~CCheckPoint();		//�f�X�g���N�^

	void SetInfo(VECTOR vPos, VECTOR vSize, float fRad);

	//�擾�֐�
	VECTOR GetPosVec() { return m_vPos; }					//���W
	VECTOR* GetpPosVec() { return &m_vPos; }		//���W�擾
	VECTOR GetSizeVec() { return m_vSize; }					//�T�C�Y
	float  GetRad() { return m_fRad; }						//���a


};
