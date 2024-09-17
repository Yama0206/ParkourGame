#include "ItemManager.h"

//��`
const char COIN_MODEL_PATH[] = { "data/Item/MagicStone.x" };
const int ITEM_MAX_NUM = 50;


CItemManager::CItemManager()
{
}

CItemManager::~CItemManager()
{
	//�A�C�e���̐�����
	for (int ItemIndex = 0; ItemIndex < m_cItemList.size(); ItemIndex++)
	{
		//�N���X������
		delete m_cItemList[ItemIndex];
	}
}

void CItemManager::Init()
{
}

void CItemManager::Load()
{
	m_cFileDataList.ReadFile();

	//�I���W�i�����f���̓ǂݍ���
	int iCoinHndl = MV1LoadModel(COIN_MODEL_PATH);

	//���f���𕡐�
	for (int ItemIndex = 0; ItemIndex < m_cFileDataList.itemInfoList.size(); ItemIndex++) {
		switch (m_cFileDataList.itemInfoList[ItemIndex].m_eType) {
		case Coin:
			//��������N���X�̃|�C���^�ϐ����쐬
			CCoin* cCoin = new CCoin();

			//��ō�����N���X�ɏ������
			cCoin->SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vRot,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
						   m_cFileDataList.itemInfoList[ItemIndex].m_IsAllive);

			cCoin->Load(iCoinHndl);

			//�A�C�e���̃��X�g��push_back����
			m_cItemList.push_back(cCoin);

			break;
		}
	}
}

void CItemManager::Step()
{

}

void CItemManager::Draw()
{
	for (int ItemIndex = 0; ItemIndex < m_cItemList.size(); ItemIndex++)
	{
		m_cItemList[ItemIndex]->Draw();
	}
}

void CItemManager::Update()
{
	for (int ItemIndex = 0; ItemIndex < m_cItemList.size(); ItemIndex++)
	{
		m_cItemList[ItemIndex]->Update();
	}
}

void CItemManager::Fin()
{

}

