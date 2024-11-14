#pragma once
#include "DxLib.h"
#include "../CheckPoint.h"
#include "../ReadList/ReadCheckPointList.h"
#include "../../Debug/DebugManager.h"
#include <vector>

using namespace std;

constexpr int PLAYER_PASSED_LIST_SIZE = 20;				//�v���C���[���ʂ����ꏊ��ۑ����Ă������X�g�̃T�C�Y

class CCheckPointManager
{
private:
	static CCheckPointManager* m_Instance;

private:
	//�x�[�X�N���X
	vector <CCheckPoint*> m_cCheckPointList;			//�`�F�b�N�|�C���g
	//�������郊�X�g�N���X
	CReadCheckPointList m_cFileDataList;				//�`�F�b�N�|�C���g�̏������郊�X�g

	int m_iPassedPlayerNum[PLAYER_PASSED_LIST_SIZE];	//�v���C���[���ʂ����ꏊ

	int m_iLastPassedPlayerNum;							//�v���C���[���Ō�ɒʂ����ꏊ

	int m_iLastPassedEnemyNum;							//�G���Ō�ɒʂ����ꏊ

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
	void Step();

	//�N���X�̃T�C�Y�擾
	inline int	GetSize() { return m_cCheckPointList.size(); }

	//�擾�֐�
	//�@iID : �`�F�b�N�|�C���g�̔ԍ�
	VECTOR	GetPosVec				(int iID)					{ return m_cCheckPointList[iID]->GetPosVec(); }							//���W
	float	GetRad					(int iID)					{ return m_cCheckPointList[iID]->GetRad(); }							//���a
	int		GetArrayIndex			(int iID)					{ return m_cCheckPointList[iID]->GetArrayIndex(); }						//�`�F�b�N�|�C���g�̎��̏ꏊ�̐�
	int		GetNextCurrentNum		(int iID, int CurrentIndex)	{ return m_cCheckPointList[iID]->GetNextCurrentNum(CurrentIndex); }		//���Ɍ������`�F�b�N�|�C���g�̔ԍ�
	int		GetPassedPlayerNum		(int iID)					{ return m_iPassedPlayerNum[iID]; }										//�v���C���[���ʂ����ꏊ�̔ԍ�(�Y�����̔ԍ���Ԃ�)
	int		GetPassedPlayerNum		();																									//�v���C���[���ʂ����ꏊ�̔ԍ�
	int		GetPassedPlayerNumSize	();
	int		GetLastPassedPlayerNum	()							{ return m_iLastPassedPlayerNum; }										//�v���C���[���Ō�ɒʂ����ԍ�
	int		GetLastPassedEnemyNum	()							{ return m_iLastPassedEnemyNum; }										//�G���Ō�ɒʂ����ԍ�

	//�ݒ�֐�
	//�@iID : �`�F�b�N�|�C���g�̔ԍ�
	void	SetPosVec				(int iID, VECTOR vPos)		{  m_cCheckPointList[iID]->SetPosVec(vPos); }							//���W
	void	SetRad					(int iID, float fRad)		{  m_cCheckPointList[iID]->SetRad(fRad); }								//���a
	void	SetPassedPlayerNum		(int iNum);																							//�v���C���[���ʂ����ԍ�
	void	InitPassedPlayerNum		(int iID)					 { m_iPassedPlayerNum[iID] = -1; }										//�v���C���[���ʂ����ԍ��̔z���Y�����̔ԍ��̕���������������
	void	SetLastPassedPlayerNum	(int iNum)					{ m_iLastPassedPlayerNum = iNum; }										//�v���C���[���Ō�ɒʂ����ԍ�
	void	SetLastPassedEnemyNum	(int iNum)					{ m_iLastPassedEnemyNum = iNum; }										//�G���Ō�ɒʂ����ԍ�

	//�v���C���[���ʂ����ꏊ�̔z����폜
	void	ClearPassedPlayerNum();																									//�v���C���[���ʂ����ԍ�
};