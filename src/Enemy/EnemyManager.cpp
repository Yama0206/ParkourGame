#include "EnemyManager.h"

//定義関連
static const char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static const int WAIT_TIME = 60;

//コンストラクタ
CEnemyManager::CEnemyManager()
{
	m_iWaitCnt = 0;
}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
}

//初期化
void CEnemyManager::Init()
{
	m_iWaitCnt = WAIT_TIME;
	for (int i = 0; i < ENEMY_NUM; i++) {
		m_cEnemy[i].Init();
	}

	//初期値設定
	InitValue();
}

//初期値設定
void CEnemyManager::InitValue()
{
	//敵の情報を読み込む
	m_cEnemyRead.ReadFile();

	//敵の数回す
	for (int EnemyIndex = 0; EnemyIndex < 5; EnemyIndex++)
	{
		//敵の情報を移す
		m_cEnemyRead.GetStructEnemy(m_sEnemy[EnemyIndex], EnemyIndex);
	}
}

void CEnemyManager::Load()
{
	//オリジナルモデルの読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);
	//モデルを複製
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
	//オリジナル削除
	MV1DeleteModel(iHndl);
}

//終了処理
void CEnemyManager::Fin()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_cEnemy[i].Fin();
	}
}

//通常処理
void CEnemyManager::Step()
{
	int iEnemyCnt = 0; //敵の出現数
	int iEnemyCnt_2 = 0;
	//敵の移動処理
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

	//敵の出現
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

//更新処理
void CEnemyManager::Draw()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_cEnemy[i].Draw();
		//m_cEnemy_2[i].Draw();
	}
}

//プレイヤーショットリクエスト
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
