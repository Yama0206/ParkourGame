#pragma once
#include "DxLib.h"


class CCheckPoint
{
private:
	VECTOR m_vPos;			//���W
	VECTOR m_vSize;			//�T�C�Y

	float m_fRad;			//���a

	int m_iCPNum;			//�`�F�b�N�|�C���g�ԍ�
	int m_NextCPNum[4];		//���Ɍ������`�F�b�N�|�C���g�̔ԍ�

	//�t���O
	bool m_PlayerHit;		//�v���C���[�������������ǂ���
	bool m_IsArrived;		//��������
public:
	CCheckPoint();			//�R���X�g���N�^
	~CCheckPoint();			//�f�X�g���N�^

	void SetInfo(int Num, VECTOR vPos, VECTOR vSize, float fRad, int* NextCPNum);

	//�擾�֐�
	VECTOR	GetPosVec()			{ return m_vPos; }				//���W
	VECTOR* GetpPosVec()		{ return &m_vPos; }				//���W�擾
	VECTOR	GetSizeVec()		{ return m_vSize; }				//�T�C�Y
	float	GetRad()			{ return m_fRad; }				//���a
	int		GetiCPNum()			{ return m_iCPNum; }			//�`�F�b�N�|�C���g�̔ԍ�
	bool	GetIsArrived()		{ return m_IsArrived; }			//���������t���O�擾
	int		GetNextNum(int iID) { return m_NextCPNum[iID]; }	//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
	

	//�ݒ�֐�
	void SetIsArrived(bool IsFrag)	{ m_IsArrived = IsFrag; }			//���������t���O
	void SetiCPNum(int Num)			{ m_iCPNum = Num; }					//�`�F�b�N�|�C���g�̔ԍ�

	//�`�F�b�N�|�C���g�ԍ��̉��Z
	void AddCPNum();

};