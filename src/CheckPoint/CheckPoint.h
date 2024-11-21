#pragma once
#include "DxLib.h"
#include <vector>

using namespace std;

//��`
constexpr int NEXT_CHECKPOINT_NUM = 4;													//���Ɍ������`�F�b�N�|�C���g���L������ϐ��̔z��̍ő吔

class CCheckPoint
{
private:
	VECTOR m_vPos;																		//���W
	VECTOR m_vSize;																		//�T�C�Y

	float m_fRad;																		//���a

	int m_iCurrentNum;																	//�`�F�b�N�|�C���g�ԍ�
	int m_NextCurrentNum[NEXT_CHECKPOINT_NUM];											//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
	int m_iArrayIndex;																	//�`�F�b�N�|�C���g�̎��Ɍ}����ꏊ�̐�

public:
	CCheckPoint();																		//�R���X�g���N�^
	~CCheckPoint();																		//�f�X�g���N�^

	//	���̐ݒ�
	void SetInfo(int Num, VECTOR vPos, float fRad, int* NextCPNum);

	//�擾�֐�
	VECTOR	GetPosVec()					{ return m_vPos; }											//���W
	VECTOR  GetSizeVec()				{ return m_vSize; }											//�T�C�Y
	float	GetRad()					{ return m_fRad; }											//���a
	int		GetArrayIndex()				{ return m_iArrayIndex; }									//�`�F�b�N�|�C���g�̎��Ɍ}����ꏊ
	int		GetCurrentNum()				{ return m_iCurrentNum; }									//�`�F�b�N�|�C���g�̔ԍ�
	int		GetNextCurrentNum(int iID)	{ return m_NextCurrentNum[iID]; }							//���Ɍ������`�F�b�N�|�C���g

	//�ݒ�֐�
	void SetPosVec			(VECTOR vPos)				{ m_vPos = vPos; }							//���W
	void SetRad				(float fRad)				{ m_fRad = fRad; }							//���a
	void SetNextCurrentNum(int CurrentNum, int iID)		{ m_NextCurrentNum[iID] = CurrentNum; }		//���Ɍ������`�F�b�N�|�C���g�̔ԍ�

	//�`�F�b�N�|�C���g�̎��Ɍ}����ꏊ�̐������Z
	void AddArayIndex() { m_iArrayIndex++; }
};		
