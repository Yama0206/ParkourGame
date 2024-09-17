#include "EnemyManager.h"

//��`�֘A
static const char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static const int WAIT_TIME = 60;

//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{

}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	//�G�̃��X�g�̐�����
	for(int BossIndex = 0; BossIndex < m_cEnemyList.size(); BossIndex++)
	{
		//�N���X������
		delete m_cEnemyList[BossIndex];
	}
}

//������
void CEnemyManager::Init()
{
}

//�����l�ݒ�
void CEnemyManager::InitValue()
{

}

void CEnemyManager::Load()
{
	//�G�̏���ǂݍ���
	m_cEnemyRead.ReadFile();

	//�I���W�i�����f���̓ǂݍ���
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);

	//�G�̎�ނ��ƂɓG�̏���ǉ����ĉ摜��ǂݍ���
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyRead.enemyInfoList.size(); EnemyIndex++) {
		switch (m_cEnemyRead.enemyInfoList[EnemyIndex].m_eType) {
		case a:
			//��������N���X�̃|�C���^�ϐ����쐬
			CNormalBoss* cNormalBoss = new CNormalBoss();

			//a�^�C�v�̓G�ɏ���ݒ�
			cNormalBoss->SetInfo(m_cEnemyRead.enemyInfoList[EnemyIndex].m_vPos,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vSpeed,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vScale,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vRot);

			//�ǂݍ���
			cNormalBoss->Load(iHndl);

			//�A�C�e�����X�g��push_buck����
			m_cEnemyList.push_back(cNormalBoss);

			break;
		}
		
	}
	//�I���W�i���폜
	MV1DeleteModel(iHndl);
}

//�I������
void CEnemyManager::Fin()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		
	}
}

//�ʏ폈��
void CEnemyManager::Step()
{
	

}

//�X�V����
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		
	}
}

//�v���C���[�V���b�g���N�G�X�g
void CEnemyManager::RequestEnemy()
{
	VECTOR vPos = VGet((float)GetRand(200) - 100.0f, 0, 200.0f);
	VECTOR vSpeed = VGet(0.0f, 0.0f, -0.5f);
	VECTOR vPos_2 = VGet((float)GetRand(200) - 100.0f, 0, 200.0f);
	VECTOR vSpeed_2 = VGet(-0.5f, 0.0f, 0.0f);
	for (int i = 0; i < ENEMY_NUM; i++)
	{
	}
}
