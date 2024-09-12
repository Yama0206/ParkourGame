#include "ItemManager.h"

//��`
const char COIN_MODEL_PATH[] = { "" };



CItemManager::CItemManager()
{
}

CItemManager::~CItemManager()
{
}

void CItemManager::Init()
{
	for (int CoinIndex = 0; CoinIndex < m_cCoin.size(); CoinIndex++) {
		m_cCoin[CoinIndex].Init();
	}
}

void CItemManager::Load()
{
	m_cItemList.ReadFile();

	//�I���W�i�����f���̓ǂݍ���
	int iHndl = MV1LoadModel(COIN_MODEL_PATH);

	//���f���𕡐�
	for (int ItemIndex = 0; ItemIndex < m_cItemList.itemInfoList.size(); ItemIndex++) {
		switch (m_cItemList.itemInfoList[ItemIndex].m_eType) {
		case a:
			//�R�C���N���X�쐬(��U���̃N���X�ɏ�����)
			CCoin Coin;
			Coin.SetInfo(m_cItemList.itemInfoList[ItemIndex].m_vPos,
						 m_cItemList.itemInfoList[ItemIndex].m_vScale,
						 m_cItemList.itemInfoList[ItemIndex].m_vRot);
			//a�^�C�v�̓G�ɏ���ݒ�
			//�����ł������̃N���X�ɓ��ꂽ����pushback����
			m_cCoin.push_back(Coin);

			break;
		case b:

			break;
		case c:

			break;
		case d:

			break;
		default:
			break;
		}
	}

}

void CItemManager::Step()
{

}

void CItemManager::Draw()
{

}

void CItemManager::Fin()
{

}

