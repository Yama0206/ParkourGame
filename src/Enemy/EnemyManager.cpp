#include "EnemyManager.h"

//��`�֘A
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;
constexpr int CHECKPOINT_NEXTCURRENT_NUM = 4;

//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{

}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	//�G����������Ă��Ȃ������牺�̏������s��Ȃ�
	if (m_cEnemyList.size() <= 0) return;

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
		//�G�̎�ނ��Ƃɓǂݍ��ޏ��𕪂���
		case a:
			//��������N���X�̃|�C���^�ϐ����쐬
			CNormalBoss* cNormalBoss = new CNormalBoss();

			//a�^�C�v�̓G�ɏ���ݒ�
			cNormalBoss->SetInfo(m_cEnemyRead.enemyInfoList[EnemyIndex].m_vPos,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vSpeed,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vScale,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vRot,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_IsActive);

			//�ǂݍ���
			cNormalBoss->Load(iHndl);

			//�G���X�g��push_buck����
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
	//�G����������Ă��Ȃ������牺�̏������s��Ȃ�
	if (m_cEnemyList.size() <= 0) return;

	//�G�̃��X�g�̐�����
	for (int BossIndex = 0; BossIndex < m_cEnemyList.size(); BossIndex++)
	{
		//�N���X������
		delete m_cEnemyList[BossIndex];
	}
}

//�ʏ폈��
void CEnemyManager::Step(VECTOR vPlayerPos)
{
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//�ʏ폈��
		m_cEnemyList[EnemyIndex]->Step();

		//�v���C���[�̒ʂ����`�F�b�N�|�C���g�Ɍ�����
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingCheckPoint)
		{
			
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
		//�v���C���[��ǐՂ���
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingPlayer)
		{
			m_cEnemyList[EnemyIndex]->TrackingPlayer(vPlayerPos);
		}
		//�G�����񃂁[�h
		if (m_cEnemyList[EnemyIndex]->GetState() == Patrol) {
			//���Ɍ������`�F�b�N�|�C���g�̏ꏊ�Ɉړ�
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
	}
}

//�X�V����
void CEnemyManager::Draw()
{
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Draw();
	}
}

void CEnemyManager::Update()
{
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Update();
	}
}


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
