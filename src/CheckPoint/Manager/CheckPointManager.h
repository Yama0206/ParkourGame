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

	eCP_Num m_eCP_Num;									//�`�F�b�N�|�C���g�ԍ�

public:
	//CCheckPointManager���擾
	static CCheckPointManager* GetInstance();

	//CCheckPointManager���폜
	static void DeleteInstance();

public:
	CCheckPointManager();
	~CCheckPointManager();

	//�ǂݍ���
	void Load();

	//�N���X�擾
	inline CCheckPoint* GetCheckPoint(int iID) { return m_cCheckPointList[iID]; }

	//	//�`�F�b�N�|�C���g���X�g�����擾
	int GetCheckPointSize()					{ return m_cCheckPointList.size(); }
	bool GetIsArrive(int iID)				{ return m_cCheckPointList[iID]->GetIsArrived(); }
	void SetIsAriive(int iID, bool IsFrag)	{  m_cCheckPointList[iID]->SetIsArrived(IsFrag); }

	eCP_Num GetCPNum()				{ return m_cCheckPointList[m_eCP_Num]->GetCPNum(); }							//�`�F�b�N�|�C���g�ԍ��̎擾
	int GetiCPNum(int iID)			{ return m_cCheckPointList[iID]->GetiCPNum(); }
	void SetCPNum(eCP_Num Num)		{ m_cCheckPointList[m_eCP_Num]->SetCPNum(Num); }								//�`�F�b�N�|�C���g�ԍ��̐ݒ�
	void SetCPNum(int Num, int iID)			{ m_cCheckPointList[iID]->SetiCPNum(Num); }
	void AddCPNum(int iID)			{ m_cCheckPointList[iID]->AddCPNum(); }										//�`�F�b�N�|�C���g�̉��Z

	//�擾�֐�
	VECTOR GetPosVec(int iID)	{ return m_cCheckPointList[iID]->GetPosVec(); }				//���W
	float  GetfRad(int iID)		{ return m_cCheckPointList[iID]->GetRad(); }				//��]�l
};