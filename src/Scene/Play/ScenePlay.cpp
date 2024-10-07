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
	m_cField.Init();			//初期化
	m_cField.UpDate();			//更新処理
	//空
	m_cSky.Init();					//初期化
	m_cSky.UpDate();				//更新処理

	cFBox.resize(FBOX_MAX_NUM);
	cRock.resize(FBOX_MAX_NUM);

	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		cFBox[FBoxIndex].Init();		//足場の箱
	}
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++)
	{
		cRock[RockIndex].Init();
	}

	//ゴール初期化
	cGoal.Init();

	//SetBlock();

	//サウンド関連
	CSoundManager::Init();
	//CSoundManager::LoadAllData();
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
}

//毎フレーム呼ぶ処理
void CPlayScene::Step()
{
	
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

		//当たり判定処理
		CCollisionManager::CheckHitShotToEnemy(m_cEnemyManager, m_cShotManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CHeckHitPlayerToGoal(m_cPlayer, cGoal);
		CCollisionManager::CheckHitPlayerToItem(m_cPlayer, m_cItemManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CheckHitEnemyToPoint(m_cEnemyManager);
		//CollisionManager::CheckHitPlayerToPoint(m_cPlayer, m_cCheckPointManager);
		
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
	}

	//カメラ切り替え処理
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		//カメラマネージャー
		m_cCameraManager.Step(m_cPlayer.GetPosition(), m_cPlayer.GetRotate());
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{

		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	}

	//エンターキーを押したら
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		//プレイのエンドシーン
		m_eSceneID = PLAY_SCENE_END;
	}

	//カメラ更新処理
	m_cCameraManager.Step(m_cPlayer.GetPosition(), m_cPlayer.GetSpd());

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
	//m_cSky.Draw();					//空描画
	cGoal.Draw();					//ゴール描画
	m_cDebug.PrintSpeed(32, 32, m_cPlayer.GetfSpd());
	m_cDebug.PrintSpeed(100, 100, m_cPlayer.m_fMoveSpeed);
	m_cDebug.PrintSpeed(100, 150, m_cPlayer.GetSpd().z);

	m_cDebug.PrintPos(500, 32, m_cEnemyManager.GetPosVec(0));
	m_cDebug.PrintPos(300, 32, CCheckPointManager::GetInstance()->GetPosVec(0));
	m_cDebug.PrintPos(300, 42, CCheckPointManager::GetInstance()->GetPosVec(1));
	m_cDebug.PrintPos(300, 52, CCheckPointManager::GetInstance()->GetPosVec(2));
	m_cDebug.PrintPos(300, 62, CCheckPointManager::GetInstance()->GetPosVec(3));
	//エネミークラス取得
	CEnemy* cEnemy = m_cEnemyManager.GetEnemy(0);
	m_cDebug.PrintNum(500, 42, cEnemy->GetCPNum());
	

	//for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
	//	cRock[RockIndex].Draw();
	//}
}

void CPlayScene::SetBlock()
{
	//足場　箱
	m_vFBoxPos[0] = { 0.0f, 0.0f, 0.0f };
	m_vFBoxPos[1] = { 0.0f, 0.0f, 60.0f };
	m_vFBoxPos[2] = { 30.0f, 0.0f, 120.0f };
	m_vFBoxPos[3] = { 0.0f, 20.0f, 180.0f };
	m_vFBoxPos[4] = { 0.0f, 0.0f, 240.0f };
	m_vFBoxPos[5] = { 0.0f, 0.0f, 300.0f };
	m_vFBoxPos[6] = { 0.0f, 0.0f, 360.0f };
	m_vFBoxPos[7] = { 60.0f, 0.0f, 440.0f};
	m_vFBoxPos[8] = { 30.0f, 30.0f, 480.0f };
	m_vFBoxPos[9] = { 80.0f, 0.0f, 500.0f };
	m_vFBoxPos[10] = { 0.0f, 0.0f, 510.0f };
	m_vFBoxPos[11] = { 0.0f, 25.0f, 560.0f };
	m_vFBoxPos[12] = { 0.0f, 40.0f, 600.0f };
	m_vFBoxPos[13] = { 0.0f, 25.0f, 660.0f };
	m_vFBoxPos[14] = { 0.0f, 0.0f, 700.0f };
	m_vFBoxPos[15] = { 0.0f, 0.0f, 730.0f };

	for (int i = 0; i < FBOX_MAX_NUM; i++)
	{
		cFBox[i].Init(m_vFBoxPos[i], m_vFBoxSize[i], m_vFBoxRot[i]);
	}

	//足場　石
	m_vRockPos[0] = { 0.0f, 0.0f, 0.0f };
	m_vRockPos[1] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[2] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[3] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[4] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[5] = { 0.0f, 0.0f, 100.0f };


	for (int i = 0; i < cRock.size(); i++)
	{
		cRock[i].Init(m_vRockPos[i], m_vRockScale[i]);
	}
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