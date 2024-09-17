#include "ItemManager.h"

//定義
const char COIN_MODEL_PATH[] = { "data/Item/MagicStone.x" };
const int ITEM_MAX_NUM = 50;


CItemManager::CItemManager()
{
}

CItemManager::~CItemManager()
{
}

void CItemManager::Init()
{

}

void CItemManager::Load()
{
	m_cFileDataList.ReadFile();

	//オリジナルモデルの読み込み
	int iCoinHndl = MV1LoadModel(COIN_MODEL_PATH);

	//モデルを複製
	for (int ItemIndex = 0; ItemIndex < m_cFileDataList.itemInfoList.size(); ItemIndex++) {
		switch (m_cFileDataList.itemInfoList[ItemIndex].m_eType) {
		case a:
			CCoin* cCoin = new CCoin();

			cCoin->SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vRot);

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
	/*for (int CoinIndex = 0; CoinIndex < m_cCoin.size(); CoinIndex++)
	{
		m_cCoin[CoinIndex].Draw();
	}*/
}

void CItemManager::Fin()
{

}

