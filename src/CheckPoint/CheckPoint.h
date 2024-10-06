#pragma once
#include "DxLib.h"

enum eCP_Num
{
	Point_1 = 1,		//�|�C���g1
	Point_2,			//�|�C���g2
	Point_3,			//�|�C���g3
	Point_4,			//�|�C���g4
	Point_5,			//�|�C���g5
};

class CCheckPoint
{
private:
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�T�C�Y
	eCP_Num m_eCP_Num;	//�`�F�b�N�|�C���g�ԍ�

	float m_fRad;		//���a

	int m_iCPNum;		//�`�F�b�N�|�C���g�ԍ�

	//�t���O
	bool m_PlayerHit;		//�v���C���[�������������ǂ���
	bool m_IsArrived;		//��������
public:
	CCheckPoint();		//�R���X�g���N�^
	~CCheckPoint();		//�f�X�g���N�^

	void SetInfo(int Num, VECTOR vPos, VECTOR vSize, float fRad);

	//�擾�֐�
	VECTOR	GetPosVec()		{ return m_vPos; }				//���W
	VECTOR* GetpPosVec()	{ return &m_vPos; }				//���W�擾
	VECTOR	GetSizeVec()	{ return m_vSize; }				//�T�C�Y
	float	GetRad()		{ return m_fRad; }				//���a
	int		GetiCPNum()		{ return m_iCPNum; }			//�`�F�b�N�|�C���g�̔ԍ�
	bool	GetIsArrived()	{ return m_IsArrived; }			//���������t���O�擾
	eCP_Num GetCPNum()		{ return m_eCP_Num; }			//�`�F�b�N�|�C���g�ԍ��̎擾
	

	//�ݒ�֐�
	void SetIsArrived(bool IsFrag)	{ m_IsArrived = IsFrag; }			//���������t���O
	void SetCPNum(eCP_Num Num)		{ m_eCP_Num = Num; }				//�`�F�b�N�|�C���g�ԍ�
	void SetiCPNum(int Num)			{ m_iCPNum = Num; }					//�`�F�b�N�|�C���g�̔ԍ�

	//�`�F�b�N�|�C���g�ԍ��̉��Z
	void AddCPNum();

};
