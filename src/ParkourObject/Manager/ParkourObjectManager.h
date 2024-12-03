#pragma once
#include "../ParkourObject.h"
#include <vector>

using namespace std;

class ParkourObjectManager
{
private:
	enum Dir {
		FRONT,			//�O
		BACK,			//���
		LEFT,			//��
		RIGHT,			//�E
	};



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
	ParkourObjectManager();
	//�f�X�g���N�^
	~ParkourObjectManager();

public:
	

};
