#pragma once
#include "DxLib.h"
#include "../Coin/Coin.h"

class CItemManager
{
private:

public:
	CItemManager();		//�R���g���N�^
	~CItemManager();	//�f�X�g���N�^

public:
	//������
	void Init();
	//�ǂݍ���
	void Load();
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();

};
