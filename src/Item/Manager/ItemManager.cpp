#include "ItemManager.h"

//��`
const char COIN_MODEL_PATH[] = { "data/Item/Coin.x" };
const int ITEM_MAX_NUM = 50;


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
		while (fprintf_s(fp, "%d, %f,%f,%f",
			&TypeNum,
			&vPos.x, &vPos.y, &vPos.z
		) != EOF) {
			//���X�g�ɒǉ�
			/*itemInfoList.push_back(m_sItemData);*/
		}
	}

	fclose(fp);
}
