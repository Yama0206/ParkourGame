#include "ScenePlay.h"

//定義関連


//コンストラクタ
CPlayScene::CPlayScene()
{
	//ひとまず初期化しておく

	m_eSceneID = PLAY_SCENE_INIT;
}

CPlayScene::~CPlayScene() {

}

int CPlayScene::Loop()
{
	int iRet = 0;
	//ここはひとまずswitch文を利用する
	switch (m_eSceneID)
	{
	case CPlayScene::PLAY_SCENE_INIT:
		Init();
		m_eSceneID = PLAY_SCENE_LOAD;
		break;
	case CPlayScene::PLAY_SCENE_LOAD:
		Load();
		CSoundManager::Play(CSoundManager::SOUNDID_BGM, DX_PLAYTYPE_LOOP);
		m_eSceneID = PLAY_SCENE_LOOP;
		break;
	case CPlayScene::PLAY_SCENE_LOOP:
		Step();
		break;
	case CPlayScene::PLAY_SCENE_END:
		iRet = Fin();
		m_eSceneID = PLAY_SCENE_INIT;
		break;
	}

	return iRet;
}

//初期化
void CPlayScene::Init()
{
	//カウント変数初期化
	m_TimeCnt = 0;
	m_FreamCnt = 0;

	//カメラの初期化
	m_cCameraManager.Init();
	m_cCameraManager.SetNearFar(5.0f, 10000.0f);
	//プレイヤー初期化
	m_cPlayer.Init();
	m_cPlayer.InitValue();
	m_cPlayer.SetSize();
	//敵初期化
	m_cEnemyManager.Init();
	//オブジェクト
	m_cObjectManager.Init();		//初期化
	m_cObjectManager.Update();		//更新処理
	//アイテム
	m_cItemManager.Init();			//初期化
	//弾の初期化
	m_cShotManager.Init();			//初期化
	//背景
	m_cField.Init();				//初期化
	m_cField.UpDate();				//更新処理
	//空
	m_cSky.Init();					//初期化
	m_cSky.UpDate();				//更新処理

	//パルクールオブジェクト
	CParkourObjectManager::GetInstance()->Init();			//初期化
	CParkourObjectManager::GetInstance()->Update();			//更新処理

	//ゴール初期化
	cGoal.Init();

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Init();
	}

	m_cLocker[0].SetPos(VGet(-231.1f, -1.0f, -135.0f));
	m_cLocker[1].SetPos(VGet(-429.0f, -1.0f, -467.0f));
	m_cLocker[2].SetPos(VGet(-556.0f, -1.0f, -671.0f));

	//サウンド関連
	CSoundManager::Init();
	//CSoundManager::LoadAllData();

	cBox.Init();
}

//終了処理
int CPlayScene::Fin()
{
	int iRet = 0;
	if (cGoal.GetIsGoal() == true)
	{
		iRet = 1;
	}
	else {
		iRet = 2;
	}

	m_cCameraManager.Fin();			//カメラマネージャー
	m_cPlayer.Fin();				//プレイヤー
	m_cEnemyManager.Fin();			//敵
	m_cObjectManager.Fin();			//オブジェクト
	m_cField.Fin();					//背景
	m_cSky.Fin();					//空

	//サウンド関連
	CSoundManager::Exit();
	
	return iRet;
}

//読み込み
void CPlayScene::Load()
{

	m_cPlayer.LoadModel(PLAYER_MODEL_PATH);						//プレイヤー
	m_cEnemyManager.Load();										//敵
	m_cObjectManager.Load();									//オブジェクト
	m_cItemManager.Load();										//アイテム
	m_cShotManager.Load();										//弾
	m_cField.Load();											//背景
	m_cSky.Load();												//空
	CCheckPointManager::GetInstance()->Load();					//チェックポイント

	//ゴール読み込み
	cGoal.Load();

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Load();
	}

	cBox.Load();
}

//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	//基準となるデバッグ関連を表示させておく
	CDebugManager::GetInstance()->AddBox(VGet(0, 10, 0), VGet(1, 1, 1));

	CDebugManager::GetInstance()->AddSphere(VGet(30, 10, 0), 1);

	//プレイヤー更新処理
	if (m_cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//プレイヤー
		m_cPlayer.Step(m_cShotManager, m_cCameraManager);
		//敵
		m_cEnemyManager.Step(m_cPlayer.GetPosition());
		//弾
		m_cShotManager.Step();
		
		//空の通常処理
		m_cSky.Step();

		CCheckPointManager::GetInstance()->Step();

		if (m_cPlayer.GetIsHide())
		{
			m_cEnemyManager.SetIsPlayerHideMode(true);
		}
		else {
			m_cEnemyManager.SetIsPlayerHideMode(false);
		}
		
		cBox.Step();

		//当たり判定処理

		CCollisionManager::CHeckHitPlayerToGoal(m_cPlayer, cGoal);
		CCollisionManager::CheckHitPlayerToItem(m_cPlayer, m_cItemManager);
		for (int i = 0; i < 3; i++) {
			CCollisionManager::CheckHitPlayerToHideObject(m_cPlayer, m_cLocker[i]);
		}
		CCollisionManager::CheckHitEnemyToPoint(m_cEnemyManager);
		CCollisionManager::CheckHitPlayerToEnemy(m_cPlayer, m_cEnemyManager);
		CCollisionManager::CheckHitPlayerToPoint(m_cPlayer, m_cEnemyManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CheckHitEnemyToField(m_cEnemyManager, m_cField);
		CCollisionManager::CheckHitPlayerToParkourObject(m_cPlayer, cBox);
		
		//更新処理--------------------------------------------------------------//
		//プレイヤー
		m_cPlayer.Update();	
		//敵
		m_cEnemyManager.Update();
		//アニメーション
		m_cPlayer.UpdateAnim();	
		//天球
		m_cSky.UpDate();
		//ゴール
		cGoal.Update();			
		//アイテム
		m_cItemManager.Update();

		for (int i = 0; i < 3; i++) {
			m_cLocker[i].Update();
		}

		cBox.Update();
	}

	//カメラ切り替え処理
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		//カメラマネージャー
		m_cCameraManager.Step(m_cPlayer.GetForcsPos(), m_cPlayer.GetRotate());
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{
		//デバッグモード
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	}

	//エンターキーを押したら
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		//プレイのエンドシーン
		m_eSceneID = PLAY_SCENE_END;
	}

	//カメラ更新処理
	m_cCameraManager.Step(m_cPlayer.GetForcsPos(), m_cPlayer.GetSpd());

	//プレイヤーが死亡したら
	GameEnd();
}

//プレイヤーが死亡した場合の処理
void CPlayScene::GameEnd()
{
	if (m_cPlayer.GetIsAllive() == false)
	{
		m_eSceneID = PLAY_SCENE_END;
	}
	if (m_cPlayer.GetIsAllive() == true && cGoal.GetIsGoal() == true)
	{
		m_eSceneID = PLAY_SCENE_END;
	}
}


//更新処理
void CPlayScene::Draw()
{
	m_cPlayer.Draw();				//プレイヤー描画
	m_cEnemyManager.Draw();			//敵の描画
	m_cItemManager.Draw();			//アイテムの描画
	m_cShotManager.Draw();			//弾の描画
	m_cField.Draw();				//背景描画
	//m_cSky.Draw();				//空描画
	cGoal.Draw();					//ゴール描画

	cBox.Draw();

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Draw();
	}

	//デバッグ
	CDebugManager::GetInstance()->Draw();
}


void CPlayScene::TimeCnt()
{
	m_FreamCnt++;

	if (m_FreamCnt >= 60)
	{
		m_TimeCnt++;
		m_FreamCnt = 0;
	}

}