#include "EnemyManager.h"

//��`�֘A
static const char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static const int WAIT_TIME = 60;

//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;
}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
}

//������
void CEnemyManager::Init()
{
	m_iWaitCnt = WAIT_TIME;
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Init();
	}

	//�����l�ݒ�
	InitValue();
}

//�����l�ݒ�
void CEnemyManager::InitValue()
{
	//�G�̏���ǂݍ���
	m_cEnemyRead.ReadFile();

	//�G�̐���
	for (int EnemyIndex = 0; EnemyIndex < 5; EnemyIndex++)
	{
		//�G�̏����ڂ�
		m_cEnemyRead.GetStructEnemy(m_sEnemy[EnemyIndex], EnemyIndex);
	}
}

void CEnemyManager::Load()
{
	//�I���W�i�����f���̓ǂݍ���
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	//���f���𕡐�
	for (int EnemyIndex = 0; EnemyIndex < ENEMY_NUM; EnemyIndex++) {
		switch (m_sEnemy[EnemyIndex].m_eType) {
		case a:
			m_cEnemy[EnemyIndex].SetInfo(m_sEnemy[EnemyIndex].m_vPos, m_sEnemy[EnemyIndex].m_vSpeed, m_sEnemy[EnemyIndex].m_vSize, m_sEnemy[EnemyIndex].m_vRot);
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
	//�I���W�i���폜
	MV1DeleteModel(iHndl);
}

//�I������
void CEnemyManager::Fin()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_cEnemy[i].Fin();
	}
}

//�ʏ폈��
void CEnemyManager::Step()
{
	int iEnemyCnt = 0; //�G�̏o����
	int iEnemyCnt_2 = 0;
	//�G�̈ړ�����
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_cEnemy[i].Step();
		/*m_cEnemy_2[i].Step();*/
		if (m_cEnemy[i].IsActiv())
		{
			iEnemyCnt++;
		}
		/*if (m_cEnemy_2[i].IsActiv())
		{
			iEnemyCnt_2++;
		}*/
	}

	//�G�̏o��
	m_iWaitCnt--;
	if (m_iWaitCnt < 0 || iEnemyCnt == 0)
	{
		RequestEnemy();
		m_iWaitCnt = WAIT_TIME;
	}
	m_iWaitCnt_2--;
	if (m_iWaitCnt_2 < 0 || iEnemyCnt_2 == 0)
	{
		RequestEnemy();
		m_iWaitCnt_2 = WAIT_TIME;
	}


}

//�X�V����
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_cEnemy[i].Draw();
		//m_cEnemy_2[i].Draw();
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
		if (m_cEnemy[i].RequestEnemy(vPos, vSpeed))
		{
			
		}
		/*if (m_cEnemy_2[i].RequestEnemy(vPos_2, vSpeed))
		{
			break;
		}*/
	}
}
