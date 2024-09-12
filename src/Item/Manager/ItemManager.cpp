#include "ItemManager.h"

//定義
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

	//オリジナルモデルの読み込み
	int iHndl = MV1LoadModel(COIN_MODEL_PATH);

	//モデルを複製
	for (int ItemIndex = 0; ItemIndex < m_cItemList.itemInfoList.size(); ItemIndex++) {
		switch (m_cItemList.itemInfoList[ItemIndex].m_eType) {
		case a:
			//コインクラス作成(一旦このクラスに情報を代入)
			CCoin Coin;
			Coin.SetInfo(m_cItemList.itemInfoList[ItemIndex].m_vPos,
						 m_cItemList.itemInfoList[ItemIndex].m_vScale,
						 m_cItemList.itemInfoList[ItemIndex].m_vRot);
			//aタイプの敵に情報を設定
			//ここでさっきのクラスに入れた情報をpushbackする
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

