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

	vector<int> m_iPassedPlayerNum;						//�v���C���[���ʂ����ꏊ

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

	//�N���X�̃T�C�Y�擾
	inline int	GetSize() { return m_cCheckPointList.size(); }

	//�擾�֐�
	//�@iID : �`�F�b�N�|�C���g�̔ԍ�
	VECTOR	GetPosVec			(int iID)					{ return m_cCheckPointList[iID]->GetPosVec(); }							//���W
	float	GetRad				(int iID)					{ return m_cCheckPointList[iID]->GetRad(); }							//���a
	bool	GetIsPassedPlayer	(int iID)					{ return m_cCheckPointList[iID]->GetPassedPlayer(); }					//�v���C���[���ʂ������ǂ���
	int		GetArrayIndex		(int iID)					{ return m_cCheckPointList[iID]->GetArrayIndex(); }						//�`�F�b�N�|�C���g�̎��̏ꏊ�̐�
	int		GetNextCurrentNum	(int iID, int CurrentIndex)	{ return m_cCheckPointList[iID]->GetNextCurrentNum(CurrentIndex); }		//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
	int		GetPassedPlayerNum	(int iID)					{ return m_iPassedPlayerNum[iID]; }										//�v���C���[���ʂ����ꏊ�̔ԍ�
	int		GetPassedPlayerNum	()							{ return m_iPassedPlayerNum.back(); }									//�v���C���[���ʂ����ꏊ�̔ԍ�
	int		GetPassedPlayerSize	()							{ return m_iPassedPlayerNum.size(); }									//�v���C���[���ʂ����ꏊ�T�C�Y

	//�ݒ�֐�
	//�@iID : �`�F�b�N�|�C���g�̔ԍ�
	void	SetPosVec			(int iID, VECTOR vPos)		{  m_cCheckPointList[iID]->SetPosVec(vPos); }					//���W
	void	SetRad				(int iID, float fRad)		{  m_cCheckPointList[iID]->SetRad(fRad); }						//���a
	void	SetIsPassedPlayer	(int iID, bool IsFrag)		{ m_cCheckPointList[iID]->SetPassedPlayer(IsFrag); }			//�v���C���[���ʂ������ǂ���
	void	SetPassedPlayerNum	(int Num)					{ m_iPassedPlayerNum.push_back(Num); }							//�v���C���[���ʂ����ꏊ�̔ԍ�

	//�v���C���[���ʂ����ꏊ�̔z����폜
	void	ClearPassedPlayerNum()							{ m_iPassedPlayerNum.clear(); }									//�v���C���[���ʂ����ꏊ�̔ԍ�
};