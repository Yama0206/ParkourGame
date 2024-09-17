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
<<<<<<< HEAD

=======
	CCoin* cCoin = new CCoin;
	Test* cTest = new Test;

	for (int ItemIndex = 0; ItemIndex < ITEM_MAX_NUM; ItemIndex++)
	{
		m_cItemList.push_back(cCoin);
	}
	for (int i = 0; i < ITEM_MAX_NUM; i++)
	{
		m_cItemList.push_back(cTest);
	}
>>>>>>> f32ce091bef08de189faf64a129534c0d7275c2c
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
<<<<<<< HEAD
			CCoin* cCoin = new CCoin();

			cCoin->SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vRot);

			m_cItemList.push_back(cCoin);
=======
			m_cItemList[ItemIndex][ItemIndex].SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
													  m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
													  m_cFileDataList.itemInfoList[ItemIndex].m_vRot);
			m_cItemList[50][50].SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
										m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
										m_cFileDataList.itemInfoList[ItemIndex].m_vRot);

		//コインクラス作成(一旦このクラスに情報を代入)
		/*CCoin Coin;
			Coin.SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
						 m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
						 m_cFileDataList.itemInfoList[ItemIndex].m_vRot);*/

			
>>>>>>> f32ce091bef08de189faf64a129534c0d7275c2c


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

