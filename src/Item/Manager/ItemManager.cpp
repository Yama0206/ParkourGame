#include "ItemManager.h"

//定義
const char COIN_MODEL_PATH[] = { "data/Item/Coin.x" };
const int ITEM_MAX_NUM = 50;

constexpr VECTOR ITEM_SCALE = { 0.1f,0.1f,0.1f };
constexpr VECTOR ITEM_ROT = { 0.0f,0.0f,0.0f };
constexpr VECTOR ITEM_SIZE = { 2.0f,2.0f,2.0f };


const char ITEM_TXT_PATH[] = { "data/File/Item/Item.txt" };

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
						   m_cFileDataList.itemInfoList[ItemIndex].m_vSize,
						   m_cFileDataList.itemInfoList[ItemIndex].m_eType,
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
	for (int ItemIndex = 0; ItemIndex < m_cItemList.size(); ItemIndex++) {
		if (m_cItemList[ItemIndex]->GetType() == Coin)
		{
			m_cItemList[ItemIndex]->Rotate();
		}
	}
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

void CItemManager::WriteFile(VECTOR vPos, int TypeNum)
{
	FILE* fp = nullptr;

	//ファイルを開く
	if (fopen_s(&fp, ITEM_TXT_PATH, "w") == 0) {
		//ファイルの読み込み、変数への保存
		fprintf_s(fp, "%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d\n",
			1,
			vPos.x, 0.0, vPos.z,
			ITEM_SCALE.x, ITEM_SCALE.y, ITEM_SCALE.z,
			ITEM_ROT.x, ITEM_ROT.y, ITEM_ROT.z,
			ITEM_SIZE.x, ITEM_SIZE.y, ITEM_SIZE.z,
			1
		);
		//リストに追加
		/*itemInfoList.push_back(m_sItemData);*/		
	}
	fclose(fp);
}
