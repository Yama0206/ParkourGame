#include "EnemyManager.h"

//定義関連
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;
constexpr int CHECKPOINT_NEXTCURRENT_NUM = 4;

//コンストラクタ
CEnemyManager::CEnemyManager()
{

}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
	//敵が生成されていなかったら下の処理を行わない
	if (m_cEnemyList.size() <= 0) return;

	//敵のリストの数分回す
	for(int BossIndex = 0; BossIndex < m_cEnemyList.size(); BossIndex++)
	{
		//クラスを消去
		delete m_cEnemyList[BossIndex];
	}
}

//初期化
void CEnemyManager::Init()
{
}

//初期値設定
void CEnemyManager::InitValue()
{

}

void CEnemyManager::Load()
{
	//敵の情報を読み込む
	m_cEnemyRead.ReadFile();

	//オリジナルモデルの読み込み
	int iHndl = MV1LoadModel(ENEMY_MODEL_PATH);

	//敵の種類ごとに敵の情報を追加して画像を読み込む
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyRead.enemyInfoList.size(); EnemyIndex++) {
		switch (m_cEnemyRead.enemyInfoList[EnemyIndex].m_eType) {
		//敵の種類ごとに読み込む情報を分ける
		case a:
			//情報を入れるクラスのポインタ変数を作成
			CNormalBoss* cNormalBoss = new CNormalBoss();

			//aタイプの敵に情報を設定
			cNormalBoss->SetInfo(m_cEnemyRead.enemyInfoList[EnemyIndex].m_vPos,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vSpeed,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vScale,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_vRot,
								 m_cEnemyRead.enemyInfoList[EnemyIndex].m_IsActive);

			//読み込み
			cNormalBoss->Load(iHndl);

			//敵リストにpush_buckする
			m_cEnemyList.push_back(cNormalBoss);

			break;
		}
		
	}
	//オリジナル削除
	MV1DeleteModel(iHndl);
}

//終了処理
void CEnemyManager::Fin()
{
	//敵が生成されていなかったら下の処理を行わない
	if (m_cEnemyList.size() <= 0) return;

	//敵のリストの数分回す
	for (int BossIndex = 0; BossIndex < m_cEnemyList.size(); BossIndex++)
	{
		//クラスを消去
		delete m_cEnemyList[BossIndex];
	}
}

//通常処理
void CEnemyManager::Step(VECTOR vPlayerPos)
{
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//通常処理
		m_cEnemyList[EnemyIndex]->Step();

		//プレイヤーの通ったチェックポイントに向かう
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingCheckPoint)
		{
			
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
		//プレイヤーを追跡する
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingPlayer)
		{
			m_cEnemyList[EnemyIndex]->TrackingPlayer(vPlayerPos);
		}
		//敵が巡回モード
		if (m_cEnemyList[EnemyIndex]->GetState() == Patrol) {
			//次に向かうチェックポイントの場所に移動
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
	}
}

//更新処理
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
