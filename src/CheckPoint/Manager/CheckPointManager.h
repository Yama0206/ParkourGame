#pragma once
#include "DxLib.h"
#include "../CheckPoint.h"
#include "../ReadList/ReadCheckPointList.h"
#include <vector>

using namespace std;


class CCheckPointManager
{
private:
	static CCheckPointManager* m_Instance;

private:
	//�x�[�X�N���X
	vector <CCheckPoint*> m_cCheckPointList;			//�`�F�b�N�|�C���g
	//�������郊�X�g�N���X
	CReadCheckPointList m_cFileDataList;				//�`�F�b�N�|�C���g�̏������郊�X�g

	//�v���C���[���ʂ����`�F�b�N�|�C���g�̔z��
	vector<int> m_ViaPlayer;

public:
	//�V���O���g���̃N���X�擾�Ɣj��--------------
	//CCheckPointManager���擾
	static CCheckPointManager* GetInstance();
	//CCheckPointManager���폜
	static void DeleteInstance();
	//--------------------------------------------

public:
	CCheckPointManager();						//�R���X�g���N�^
	~CCheckPointManager();						//�f�X�g���N�^

	//�ǂݍ���
	void Load();

	//�N���X�擾
	inline CCheckPoint* GetCheckPoint(int iID) { return m_cCheckPointList[iID]; }								//�`�F�b�N�|�C���g�N���X�擾(�����炭�����g��Ȃ�)

	//	//�`�F�b�N�|�C���g���X�g�����擾
	int		 GetCheckPointSize()					{ return m_cCheckPointList.size(); }						//�`�F�b�N�|�C���g�N���X�̃T�C�Y���擾
	bool	 GetIsArrive(int iID)				{ return m_cCheckPointList[iID]->GetIsArrived(); }				//�����������ǂ����̃t���O���擾
	void	 SetIsAriive(int iID, bool IsFrag)	{ m_cCheckPointList[iID]->SetIsArrived(IsFrag); }				//�����������ǂ����̃t���O�̐ݒ�

	int		 GetiCPNum(int iID)					{ return m_cCheckPointList[iID]->GetiCPNum(); }					//���Ɍ������ꏊ�̔ԍ����擾
	void	 AddCPNum(int iID)					{ m_cCheckPointList[iID]->AddCPNum(); }							//�`�F�b�N�|�C���g�̉��Z

	int		 GetNextNum(int Num, int iID)		{ return m_cCheckPointList[iID]->GetNextNum(Num); }				//���Ɍ������`�F�b�N�|�C���g�̔ԍ�

	//�擾�֐�
	VECTOR	GetPosVec(int iID)				{ return m_cCheckPointList[iID]->GetPosVec(); }						//���W
	float	GetfRad(int iID)				{ return m_cCheckPointList[iID]->GetRad(); }						//��]�l
	int		GetViaPlayer()					{ return m_ViaPlayer.back(); }										//�v���C���[���ʂ����ꏊ�̔ԍ��̔z��̖����̗v�f��Ԃ�
	int		GetViaPlayerSize()				{ return m_ViaPlayer.size(); }										//�v���C���[���ʂ����ꏊ�̔ԍ��̔z��̃T�C�Y��Ԃ�

	//�ݒ�֐�
	void	SetCPNum(int Num, int iID)		{ m_cCheckPointList[iID]->SetiCPNum(Num); }							//���Ɍ������ꏊ�̔ԍ���ݒ�
	void	SetViaPlayer(int iID);																				//�v���C���[�������ꏊ�̔ԍ����L��
};