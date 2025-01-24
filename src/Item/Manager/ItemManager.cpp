#include "ItemManager.h"

//��`
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
						   m_cFileDataList.itemInfoList[ItemIndex].m_vSize,
						   m_cFileDataList.itemInfoList[ItemIndex].m_eType,
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

	//�t�@�C�����J��
	if (fopen_s(&fp, ITEM_TXT_PATH, "w") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		fprintf_s(fp, "%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d\n",
			1,
			vPos.x, 0.0, vPos.z,
			ITEM_SCALE.x, ITEM_SCALE.y, ITEM_SCALE.z,
			ITEM_ROT.x, ITEM_ROT.y, ITEM_ROT.z,
			ITEM_SIZE.x, ITEM_SIZE.y, ITEM_SIZE.z,
			1
		);
		//���X�g�ɒǉ�
		/*itemInfoList.push_back(m_sItemData);*/		
	}
	fclose(fp);
}
