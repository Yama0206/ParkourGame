#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include "../Coin/Coin.h"
#include "../../Object/ObjectManager.h"
#include "../../Read/ItemList/ItemList.h"

using namespace std;

class CItemManager : public CObjectManager
{
private:
	//��ނ�������Ƃ����̃N���X��������
	vector<CCoin> m_cCoin;
	//�A�C�e���̏���ǂݍ��ނ��߂̃N���X
	CItemList m_cItemList;

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
