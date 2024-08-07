#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/CollisionManager.h"

//定義
const char TITLE_BACKIMG_PATH[] = { "data/Title/ゲーム課題　タイトル画面.png" };		//背景画像パス
const char TITLE_STARTIMG_PAHT[] = { "data/Title/ゲームスタート.png" };		//スタート画像パス
const char TITLE_FINIMG_PAHT[] = { "data/Title/4442m.png" };		//ゲーム終了画像パス
const char TITLE_IMG_PATH[] = { "data/Title/TitleName.png" };			//タイトル画像パス

struct SBackImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct SStartImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct SFinImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct STitleImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

class CTitle
{
private:
	enum tagTITLE_SCENE {
		TITLE_SCENE_INIT,
		TITLE_SCENE_LOAD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE m_eSceneID;				//シーン保存

	SBackImg m_sBackImg;		//背景画像の構造体
	STitleImg m_sTitleImg;	//タイトル画像の構造体
	SStartImg m_sStartImg;	//スタート画像の構造体
	SFinImg m_sFinImg;		//終了画像の構造体

	int MousePosX;		//マウスのX座標
	int MousePosY;		//マウスのY座標

public:
	//コンストラクタ・デストラクタ
	CTitle();
	~CTitle();


	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();

private:
	//初期化
	void Init();
	//終了処理
	void Fin();
	//データロード
	void Load();
	//毎フレーム
	void Step();
};
