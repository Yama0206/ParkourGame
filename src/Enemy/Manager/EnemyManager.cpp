#include "EnemyManager.h"

//定義関連
static constexpr char ENEMY_MODEL_PATH[] = { "Data/enemy/enemy.pmx" };
static constexpr int WAIT_TIME = 60;
constexpr int CHECKPOINT_NEXTCURRENT_NUM = 4;

constexpr VECTOR ENEMY_SIZE = { 50,50,50 };

//コンストラクタ
CEnemyManager::CEnemyManager()
{
	EnemyGoSize = -1;
	m_IsPlayerIsHideMode = false;
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
	EnemyGoSize = -1;
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

			//サイズ
			cNormalBoss->SetSizeVec(ENEMY_SIZE);

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
	if (CInput::IsKeyPush(KEY_INPUT_2))
	{
		for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
		{
			m_cEnemyList[EnemyIndex]->SetTelePort(true);
		}
	}

	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//通常処理
		m_cEnemyList[EnemyIndex]->Step();

		if (m_IsPlayerIsHideMode)
		{
			m_cEnemyList[EnemyIndex]->SetState(Patrol);
		}

		//プレイヤーの通ったチェックポイントに向かう
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingCheckPoint)
		{
			//1F前の敵の状態がチェックポイントに向かう以外だったら
			if (m_cEnemyList[EnemyIndex]->GetOldState() != TrackingCheckPoint) {
				EnemyGoSize = CCheckPointManager::GetInstance()->GetPassedPlayerNumSize();
			}
			//配列の添え字をセット
			//敵が指定されたチェックポイントを通っていたら
			if (CCheckPointManager::GetInstance()->GetLastPassedEnemyNum() == CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize)) {
				//通った配列の番号を初期化する
				CCheckPointManager::GetInstance()->InitPassedPlayerNum(EnemyGoSize);
				EnemyGoSize++;
			}

			//何も通ってなかったら
			if (CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize) == -1)
			{
				//プレイヤーを直接追いかける
				m_cEnemyList[EnemyIndex]->SetState(TrackingPlayer);
				continue;
			}
			//プレイヤーが通った場所の配列の何番目を参照するか決める
			m_cEnemyList[EnemyIndex]->SetNextCheckPointNum(CCheckPointManager::GetInstance()->GetPassedPlayerNum(EnemyGoSize));

			//チェックポイントに向かう処理
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
			
		}
		//プレイヤーを追跡する
		if (m_cEnemyList[EnemyIndex]->GetState() == TrackingPlayer)
		{
			//次に向かう場所を初期化
			m_cEnemyList[EnemyIndex]->ClearNextPassedCheckPoint();

			//1F前がプレイヤーを追いかける以外の状態だったら
			if (m_cEnemyList[EnemyIndex]->GetOldState() != TrackingPlayer) {
				//プレイヤーが通った場所を初期化する
				CCheckPointManager::GetInstance()->ClearPassedPlayerNum();
			}
			//プレイヤーを追いかける
			m_cEnemyList[EnemyIndex]->TrackingPlayer(vPlayerPos);
		}
		//敵が巡回モード
		if (m_cEnemyList[EnemyIndex]->GetState() == Patrol) {
			//次に向かうチェックポイント番号が初期化されていたら
			if (m_cEnemyList[EnemyIndex]->GetNextCheckPointNum() == -1)
			{
				//最後に通った場所初期化
				m_cEnemyList[EnemyIndex]->ClearLastPassedCheckPoint();
				CCheckPointManager::GetInstance()->ClearLastPassedEnemyNum();
				//一番近くのチェックポイントを探す
				m_cEnemyList[EnemyIndex]->NearCheckPointFind();
				CDebugManager::GetInstance()->AddFormatString(700, 700, "%d", m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
			}
			//次に向かうチェックポイントに向かわせる
			m_cEnemyList[EnemyIndex]->TrackingCheckPoint(m_cEnemyList[EnemyIndex]->GetNextCheckPointNum());
		}
	}
}

//更新処理
void CEnemyManager::Draw()
{
	//敵の数分for文を回す
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Draw();
	}
}

void CEnemyManager::Update()
{
	//敵の数分for文を回す
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		m_cEnemyList[EnemyIndex]->Update();
	}
}

void CEnemyManager::Teleport(VECTOR vPos)
{
	//敵の数分for文を回す
	for (int EnemyIndex = 0; EnemyIndex < m_cEnemyList.size(); EnemyIndex++)
	{
		//テレポートフラグの確認
		if (m_cEnemyList[EnemyIndex]->GetTeleport())
		{
			//テレポート処理
			m_cEnemyList[EnemyIndex]->SetPosVec(vPos);

			//フラグをOFFにする
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
