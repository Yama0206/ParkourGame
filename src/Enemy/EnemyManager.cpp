#include "EnemyManager.h"

//定義関連
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;

//コンストラクタ
CEnemyManager::CEnemyManager()
{

}

//デストラクタ
CEnemyManager::~CEnemyManager()
{
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

			//アイテムリストにpush_buckする
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
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		
	}
}

//通常処理
void CEnemyManager::Step(VECTOR vPlayerPos)
{
	//敵の追跡と巡回切り替え
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

//更新処理
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

//プレイヤーを追跡する
void CEnemyManager::TrackingPlayer(VECTOR vPlayerPos, int Index)
{
		//ホーミング処理
		VECTOR PlayerVec;
		//敵からプレイヤーに向かうベクトル
		PlayerVec.x = vPlayerPos.x - m_cEnemyList[Index]->GetPosVec().x;
		PlayerVec.y = 0.0f;
		PlayerVec.z = vPlayerPos.z - m_cEnemyList[Index]->GetPosVec().z;

		float fCrossZ = 0.0f;

		//現在の進行方向のベクトル
		VECTOR  MoveVec;

		memset(&MoveVec, 0.0f, sizeof(MoveVec));

		MoveVec.x = sinf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = cosf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;

		//2つのベクトルの外積を計算
		fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

		//fCrossZの計算結果で左右の判定を行う
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
	//ホーミング処理
	VECTOR CheckPosVec;
	//敵からチェックポイント向かうベクトル
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CCheckPointManager::GetInstance()->GetiCPNum(m_cEnemyList[Index]->GetCPNum())).x - m_cEnemyList[Index]->GetPosVec().x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CCheckPointManager::GetInstance()->GetiCPNum(m_cEnemyList[Index]->GetCPNum())).z - m_cEnemyList[Index]->GetPosVec().z;

	float fCrossZ = 0.0f;

	//現在の進行方向のベクトル
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_cEnemyList[Index]->GetRotVec().y) * -1.0f;

	//2つのベクトルの外積を計算
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZの計算結果で左右の判定を行う
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
	//ホーミング処理
	VECTOR CheckPosVec;
	//敵からチェックポイント向かうベクトル
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - m_cEnemyList[EnemyIndex]->GetPosVec().x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z - m_cEnemyList[EnemyIndex]->GetPosVec().z;

	float fCrossZ = 0.0f;

	//現在の進行方向のベクトル
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_cEnemyList[EnemyIndex]->GetRotVec().y) * -1.0f;

	//2つのベクトルの外積を計算
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZの計算結果で左右の判定を行う
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

//プレイヤーショットリクエスト
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
