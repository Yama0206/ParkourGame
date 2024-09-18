#pragma once
#include "DxLib.h"
#include <iostream>
#include <vector>
#include "../ItemBase/ItemBase.h"
#include "../Coin/Coin.h"
#include "../Test.h"
#include "../../Object/ObjectManager.h"
#include "../../Read/ReadItemList/ReadItemList.h"

using namespace std;

class CItemManager : public CObjectManager
{
private:
	//�|���t�H�[�t�B�Y��
	//�x�[�X�N���X��vector�^�Ő錾
	vector<CItemBase *> m_cItemList;

	//�A�C�e���̏���ǂݍ��ނ��߂̃N���X
	CReadItemList m_cFileDataList;

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
	//�X�V����
	void Update();

	//�A�C�e�����X�g�N���X���擾
	inline CItemBase* GetItem(int iID) { return m_cItemList[iID]; }

	//�A�C�e�����X�g�̐����擾
	int GetItemSize() { return m_cItemList.size(); }

};
