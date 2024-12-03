#pragma once
#include "../ParkourObject.h"
#include "../../Read/ReadParkourObjectList/ReadParkourObjectList.h"
#include <vector>

using namespace std;

class CParkourObjectManager
{
private:
	//�C���X�^���X
	static CParkourObjectManager* m_Instance;

private:
	enum Dir {
		FRONT,			//�O
		BACK,			//���
		LEFT,			//��
		RIGHT,			//�E
	};

	//�x�[�X�N���X
	vector<CParkourObject*> m_cParkourObjectList;

	//�ǂݍ��݃��X�g�N���X
	ReadParkourObjectList m_cFileDataList;

public:
	//�C���X�^���X�擾
		//CCheckPointManager���擾
	static CParkourObjectManager* GetInstance();
	//CCheckPointManager���폜
	static void DeleteInstance();

public:
	// ������
	void Init();
	// �ǂݍ���
	void Load();
	// �`�揈��
	void Draw();
	// �X�V����
	void Update();

public:
	//�R���X�g���N�^
	CParkourObjectManager();
	//�f�X�g���N�^
	~CParkourObjectManager();

public:
	//�A�C�e�����X�g�N���X���擾
	inline CParkourObject* GetParkourObject(int iID) { return m_cParkourObjectList[iID]; }

	//�A�C�e�����X�g�̐����擾
	int GetParkourObjectSize() { return m_cParkourObjectList.size(); }

};
