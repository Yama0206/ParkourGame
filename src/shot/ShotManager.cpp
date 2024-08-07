#include "ShotManager.h"

//定義関連
static const char PLSHOT_MODEL_PATH[] = { "data/shot/plshot.x" };

//コンストラクタ
CShotManager::CShotManager()
{
}

//デストラクタ
CShotManager::~CShotManager()
{
}

//初期化
void CShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Init();
	}
}

void CShotManager::Load()
{
	//オリジナルモデルの読み込み
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	//モデルを複製
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Load(iHndl);
	}
	//オリジナル削除
	MV1DeleteModel(iHndl);
}

//終了処理
void CShotManager::Fin()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Fin();
	}
}

//通常処理
void CShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Step();
	}
}

//更新処理
void CShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Draw();
	}
}

//プレイヤーショットリクエスト
void CShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		if (cPlayerShot[i].RequestShot(vPos, vSpeed))
		{
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLSHOT);
			break;
		}
	}
}

