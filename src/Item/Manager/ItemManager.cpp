#include "ItemManager.h"

//定義
const char COIN_MODEL_PATH[] = { "data/Item/MagicStone.x" };
const int ITEM_MAX_NUM = 50;


CItemManager::CItemManager()
{
}

CItemManager::~CItemManager()
{
	//アイテムの数分回す
	for (int ItemIndex = 0; ItemIndex < m_cItemList.size(); ItemIndex++)
	{
		//クラスを消去
		delete m_cItemList[ItemIndex];
	}
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
		case Coin:
			//情報を入れるクラスのポインタ変数を作成
			CCoin* cCoin = new CCoin();

			//上で作ったクラスに情報を入力
			cCoin->SetInfo(m_cFileDataList.itemInfoList[ItemIndex].m_vPos,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vRot,
						   m_cFileDataList.itemInfoList[ItemIndex].m_vScale,
						   m_cFileDataList.itemInfoList[ItemIndex].m_IsAllive);

			cCoin->Load(iCoinHndl);

			//アイテムのリストにpush_backする
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

