#include "EnemyManager.h"

//��`�֘A
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;

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
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vRot,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_IsActive);

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
void CEnemyManager::Step(VECTOR vPlayerPos)
{
	//�G�̒ǐՂƏ���؂�ւ�
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		if (m_cEnemyList[EnemyIndex]->GetState() == Patrol) {
			TrackingCheckPoint(EnemyIndex);
		}
		else if (m_cEnemyList[EnemyIndex]->GetState() == Tracking)
		{
			if (CCheckPointManager::GetInstance()->GetViaPlayerSize() > 0) {
				TrackingPassedPlayerPoint(EnemyIndex, CCheckPointManager::GetInstance()->GetViaPlayer());
				/*TrackingPlayer(vPlayerPos, EnemyIndex);*/
			}
		}

	}
}

//�X�V����
void CEnemyManager::Draw()
{
	for (int i = 0; i < m_cEnemyList.size(); i++)
	{
		m_cEnemyList[i]->Draw();
	}
}

void CEnemyManager::Update()
{
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Update();
	}
}

//�v���C���[��ǐՂ���
void CEnemyManager::TrackingPlayer(VECTOR vPlayerPos, int Index)
{
		//�z�[�~���O����
		VECTOR PlayerVec;
		//�G����v���C���[�Ɍ������x�N�g��
		PlayerVec.x = vPlayerPos.x - m_cEnemyList[Index]->GetPosVec().x;
		PlayerVec.y = 0.0f;
		PlayerVec.z = vPlayerPos.z - m_cEnemyList[Index]->GetPosVec().z;

		float fCrossZ = 0.0f;

		//���݂̐i�s�����̃x�N�g��
		VECTOR  MoveVec;

		memset(&MoveVec, 0.0f, sizeof(MoveVec));

		MoveVec.x = sinf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = cosf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;

		//2�̃x�N�g���̊O�ς��v�Z
		fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

		//fCrossZ�̌v�Z���ʂō��E�̔�����s��
		if (fCrossZ > 0)
		{
			m_cEnemyList[Index]->SetRotVec_Y(m_cEnemyList[Index]->GetRotVec().y + 0.1);
		}
		else if (fCrossZ < 0)
		{
			m_cEnemyList[Index]->SetRotVec_Y(m_cEnemyList[Index]->GetRotVec().y - 0.1);
		}

		m_cEnemyList[Index]->SetPosVec_X(m_cEnemyList[Index]->GetPosVec().x + sinf(m_cEnemyList[Index]->GetRotVec().y) * -m_cEnemyList[Index]->GetSpeedVec().x);
		m_cEnemyList[Index]->SetPosVec_Z(m_cEnemyList[Index]->GetPosVec().z + cosf(m_cEnemyList[Index]->GetRotVec().y) * -m_cEnemyList[Index]->GetSpeedVec().z);
}

void CEnemyManager::TrackingCheckPoint(int Index)
{
	//�z�[�~���O����
	VECTOR CheckPosVec;
	//�G����`�F�b�N�|�C���g�������x�N�g��
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CCheckPointManager::GetInstance()->GetiCPNum(m_cEnemyList[Index]->GetCPNum())).x - m_cEnemyList[Index]->GetPosVec().x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CCheckPointManager::GetInstance()->GetiCPNum(m_cEnemyList[Index]->GetCPNum())).z - m_cEnemyList[Index]->GetPosVec().z;

	float fCrossZ = 0.0f;

	//���݂̐i�s�����̃x�N�g��
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;

	//2�̃x�N�g���̊O�ς��v�Z
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZ�̌v�Z���ʂō��E�̔�����s��
	if (fCrossZ > 0)
	{
		m_cEnemyList[Index]->SetRotVec_Y(m_cEnemyList[Index]->GetRotVec().y + 0.1);
	}
	else if (fCrossZ < 0)
	{
		m_cEnemyList[Index]->SetRotVec_Y(m_cEnemyList[Index]->GetRotVec().y - 0.1);
	}

	m_cEnemyList[Index]->SetPosVec_X(m_cEnemyList[Index]->GetPosVec().x + sinf(m_cEnemyList[Index]->GetRotVec().y) * -m_cEnemyList[Index]->GetSpeedVec().x);
	m_cEnemyList[Index]->SetPosVec_Z(m_cEnemyList[Index]->GetPosVec().z + cosf(m_cEnemyList[Index]->GetRotVec().y) * -m_cEnemyList[Index]->GetSpeedVec().z);
}

void CEnemyManager::TrackingPassedPlayerPoint(int EnemyIndex, int CheckPointIndex)
{
	//�z�[�~���O����
	VECTOR CheckPosVec;
	//�G����`�F�b�N�|�C���g�������x�N�g��
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - m_cEnemyList[EnemyIndex]->GetPosVec().x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z - m_cEnemyList[EnemyIndex]->GetPosVec().z;

	float fCrossZ = 0.0f;

	//���݂̐i�s�����̃x�N�g��
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -1.0f;

	//2�̃x�N�g���̊O�ς��v�Z
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZ�̌v�Z���ʂō��E�̔�����s��
	if (fCrossZ > 0)
	{
		m_cEnemyList[EnemyIndex]->SetRotVec_Y(m_cEnemyList[EnemyIndex]->GetRotVec().y + 0.1);
	}
	else if (fCrossZ < 0)
	{
		m_cEnemyList[EnemyIndex]->SetRotVec_Y(m_cEnemyList[EnemyIndex]->GetRotVec().y - 0.1);
	}

	m_cEnemyList[EnemyIndex]->SetPosVec_X(m_cEnemyList[EnemyIndex]->GetPosVec().x + sinf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -m_cEnemyList[EnemyIndex]->GetSpeedVec().x);
	m_cEnemyList[EnemyIndex]->SetPosVec_Z(m_cEnemyList[EnemyIndex]->GetPosVec().z + cosf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -m_cEnemyList[EnemyIndex]->GetSpeedVec().z);
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
