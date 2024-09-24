#pragma once
#include "DxLib.h"
#include <vector>
#include <iostream>
#include "../../Input/Input.h"
#include "../../Camera/CameraManager.h"
#include "../../Player/Player.h"
#include "../../Field/Field.h"
#include "../../shot/ShotManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Object/ObjectManager.h"
#include "../../Collision/CollisionManager.h"
#include "../../System/Sound/SoundManager.h"
#include "../../Field/Sky/Sky.h"
#include "../../Box/Box.h"
#include "../../Box/FootBox.h"
#include "../../Box/Rock.h"
#include "../../Goal/Goal.h"
#include "../../Item/Manager/ItemManager.h"

using namespace std;

class CPlayScene
{
private:
	enum tagPLAY_SCENE {
		PLAY_SCENE_INIT,
		PLAY_SCENE_LOAD,
		PLAY_SCENE_LOOP,
		PLAY_SCENE_END,

		PLAY_SCENE_NUM
	};

	CCameraManager m_cCameraManager;			//カメラマネージャー
	CShotManager m_cShotManager;				//弾の発射
	CPlayer m_cPlayer;							//プレイヤー処理
	CEnemyManager m_cEnemyManager;				//敵
	CObjectManager m_cObjectManager;			//オブジェクト
	CItemManager m_cItemManager;				//アイテムマネージャー
	BackGround m_cBackGround;					//背景処理
	CSky m_cSky;								//空
	tagPLAY_SCENE m_eSceneID;					//シーン保存

	//仮
	CBox cBox;		//箱
	vector<CFootBox> cFBox;	//足場の箱
	vector<CRock>    cRock;	//足場の石
	CGoal			 cGoal;	//ゴール

	vector<VECTOR> m_vFBoxPos;			//足場の箱の座標
	vector<VECTOR> m_vFBoxSize;			//足場の箱の大きさ
	vector<VECTOR> m_vFBoxRot;			//足場の箱の角度
	vector<VECTOR> m_vRockPos;			//足場の石の座標
	vector<VECTOR> m_vRockScale;		//足場の石の大きさ
	vector<VECTOR> m_vRockRot;			//足場の石の角度

	//プレイ時間をカウントする用の変数
	int m_TimeCnt;
	//プレイ画面のフレームをカウントする変数
	int m_FreamCnt;

public:
	//コンストラクタ・デストラクタ
	CPlayScene();
	~CPlayScene();


	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();

private:
	//初期化
	void Init();
	//終了処理
	int Fin();
	//データロード
	void Load();
	//毎フレーム
	void Step();

	//プレイヤーの死亡処理
	void GameEnd();

	//ブロックを設置
	void SetBlock();

	//プレイ時間をカウントする関数
	void TimeCnt();

};
