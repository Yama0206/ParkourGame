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
	CReadCheckPointList m_cFileDataList;		//�`�F�b�N�|�C���g�̏������郊�X�g

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
	int GetCheckPointSize() { return m_cCheckPointList.size(); }

	//���W�擾
	VECTOR GetPosVec(int iID) { return m_cCheckPointList[iID]->GetPosVec(); }

};