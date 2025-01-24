#include "EnemyManager.h"

//��`�֘A
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;
constexpr int CHECKPOINT_NEXTCURRENT_NUM = 4;

constexpr VECTOR ENEMY_SIZE = { 50,50,50 };

//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	EnemyGoSize = -1;
	m_IsPlayerIsHideMode = false;
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
	EnemyGoSize = -1;
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

			//�T�C�Y
			cNormalBoss->SetSizeVec(ENEMY_SIZE);

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
	if (CInput::IsKeyPush(KEY_INPUT_2))
	{
		for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
		{
			m_cEnemyList[EnemyIndex]->SetTelePort(true);
		}
	}

	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//�ʏ폈��
		m_cEnemyList[EnemyIndex]->Step();

		if (m_IsPlayerIsHideMode)
		{
			m_cEnemyList[EnemyIndex]->SetState(Patrol);
		}

		//�v���C���[�̒ʂ����`�F�b�N�|�C���g�Ɍ�����
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingCheckPoint)
		{
			//1F�O�̓G�̏�Ԃ��`�F�b�N�|�C���g�Ɍ������ȊO��������
			if (m_cEnemyList[EnemyIndex]->GetOldState() != TrackingCheckPoint) {
				EnemyGoSize = CCheckPointManager::GetInstance()->GetPassedPlayerNumSize();
			}
			//�z��̓Y�������Z�b�g
			//�G���w�肳�ꂽ�`�F�b�N�|�C���g��ʂ��Ă�����
			if (CCheckPointManager::GetInstance()->GetLastPassedEnemyNum() == CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize)) {
				//�ʂ����z��̔ԍ�������������
				CCheckPointManager::GetInstance()->InitPassedPlayerNum(EnemyGoSize);
				EnemyGoSize++;
			}

			//�����ʂ��ĂȂ�������
			if (CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize) == -1)
			{
				//�v���C���[�𒼐ڒǂ�������
				m_cEnemyList[EnemyIndex]->SetState(TrackingPlayer);
				continue;
			}
			//�v���C���[���ʂ����ꏊ�̔z��̉��Ԗڂ��Q�Ƃ��邩���߂�
			m_cEnemyList[EnemyIndex]->SetNextCheckPointNum(CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize));

			//�`�F�b�N�|�C���g�Ɍ���������
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
			
		}
		//�v���C���[��ǐՂ���
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingPlayer)
		{
			//���Ɍ������ꏊ��������
			m_cEnemyList[EnemyIndex]->ClearNextPassedCheckPoint();

			//1F�O���v���C���[��ǂ�������ȊO�̏�Ԃ�������
			if (m_cEnemyList[EnemyIndex]->GetOldState() != TrackingPlayer) {
				//�v���C���[���ʂ����ꏊ������������
				CCheckPointManager::GetInstance()->ClearPassedPlayerNum();
			}
			//�v���C���[��ǂ�������
			m_cEnemyList[EnemyIndex]->TrackingPlayer(vPlayerPos);
		}
		//�G�����񃂁[�h
		if (m_cEnemyList[EnemyIndex]->GetState() == Patrol) {
			//���Ɍ������`�F�b�N�|�C���g�ԍ�������������Ă�����
			if (m_cEnemyList[EnemyIndex]->GetNextCheckPointNum() == -1)
			{
				//�Ō�ɒʂ����ꏊ������
				m_cEnemyList[EnemyIndex]->ClearLastPassedCheckPoint();
				CCheckPointManager::GetInstance()->ClearLastPassedEnemyNum();
				//��ԋ߂��̃`�F�b�N�|�C���g��T��
				m_cEnemyList[EnemyIndex]->NearCheckPointFind();
				CDebugManager::GetInstance()->AddFormatString(700, 700, "%d", m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
			}
			//���Ɍ������`�F�b�N�|�C���g�Ɍ����킹��
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
	}
}

//�X�V����
void CEnemyManager::Draw()
{
	//�G�̐���for������
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Draw();
	}
}

void CEnemyManager::Update()
{
	//�G�̐���for������
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Update();
	}
}

void CEnemyManager::Teleport(VECTOR vPos)
{
	//�G�̐���for������
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//�e���|�[�g�t���O�̊m�F
		if (m_cEnemyList[EnemyIndex]->GetTeleport())
		{
			//�e���|�[�g����
			m_cEnemyList[EnemyIndex]->SetPosVec(vPos);

			//�t���O��OFF�ɂ���
			m_cEnemyList[EnemyIndex]->SetTelePort(false);
		}
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
