#pragma once

#include "Dxlib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../shot/ShotManager.h"
#include "../Model/Model.h"
#include "../Math/Math.h"
#include "../Camera/CameraManager.h"

static const char PLAYER_MODEL_PATH[]	
= { "data/char/char.pmd" };									//ロードするファイル名
static const float PLAYER_RADIUS = 2.5f;					//プレイヤーの半径

static const float PLAYER_WIDTH = 10.0f;					//プレイヤーの横サイズ
static const float PLAYER_HEIGHT = 18.0f;					//プレイヤーの縦サイズ
static const float PLAYER_DEPTH = 10.0f;					//プレイヤーの奥行き
static const float PLAYER_HALF_HEIGHT = 9.0f;				//プレイヤーの高さの半分の大きさ
static const float PLAYER_HALF_WIDHT = 5.0f;				//プレイヤーの横幅の半分の大きさ
static const int   PLAYER_DIR_NUM = 6;						//プレイヤーの向きの数

class CPlayer : public CModel
{
private:
	//プレイヤーの状態
	enum tagPlayerState {
		PLAYER_STATE_NORMAL,		//待機・歩き中
		PLAYER_STATE_JUMP,			//ジャンプ中
		PLAYER_STATE_DASH,			//走り中

		PLAYER_STATE_NUM
	};

	//アニメーション一覧
	enum tagAnim {
		ANIMID_DEFAULT,			//デフォルトモーション
		ANIMID_WALK,			//歩きモーション
		ANIMID_RUN,				//走りモーション
		ANIMID_WAIT,			//ぶらぶら
		ANIMID_UPDOWN,			//くねくね上下
		ANIMID_SHAKE,			//手を振る
		ANIMID_PIANO,			//ピアノを引いて要るっぽい
		ANIMID_DANCE,			//踊ってる

		ANIMID_NUM				//全アニメーション数
	};

	//向いている方向
	enum tagDir {
		UP = 0,		//上方向
		DOWN,		//下方向
		LEFT,		//左方向
		RIGHT,		//右方向
		FRONT,		//前方向
		BACK,		//後ろ方向
	
	};

	tagPlayerState m_eState;		//プレイヤーの状態
	tagDir m_eDir;					//プレイヤーの方向
	
	VECTOR m_ViewRot;				//プレイヤーの見ている向き
	float fChangeRot;				//プレイヤーの方向を少しずつ回転させる用の変数

	//フラグ
	bool m_IsHit;			//プレイヤーが物体に当たっているかどうか
	bool m_IsHitSide;		//プレイヤーが物体と横方向で当たった時
	bool m_IsHitLength;		//プレイヤーが物体と縦方向で当たった時
	bool m_IsJump;			//プレイヤーがジャンプしたかどうか
	bool m_IsKeyHit;		//キーを押したかどうか

public:
	//コンストラクタ
	CPlayer();
	~CPlayer();

	//初期値設定
	void InitValue();

	//通常処理
	void Step(CShotManager& cShotManager, CCameraManager& cCameraManager);
	//更新したデータを反映させる
	void Update();

	//描画処理
	void Draw();

	//操作処理
	void Control(VECTOR vRot);
	//ジャンプ処理
	void Jamp();
	//重力計算
	void Gravity();
	//弾の発射処理
	void Shot(CShotManager& cShotManager);

	//座標設定
	VECTOR SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void   SetPosX(float vPosX);					//X座標
	void   SetPosY(float vPosY);					//Y座標
	void   SetPosZ(float vPosZ);					//Z座標
	void   SetNextPosX(float vNextPosX);			//移動後のX座標
	void   SetNextPosY(float vNextPosY);			//移動後のY座標
	void   SetNextPosZ(float vNextosZ);				//移動後のZ座標
	//サイズ設定
	VECTOR SetSize();

	//データ関連の破棄
	void Delete();
	//終了処理
	void Fin();

	//取得・設定関連
	//進んでいる方向チェック
	void GetMoveDir(bool* _DirArray);	
	//方向を変える
	void ChangeDir(int FreamCnt);

	//座標取得
	inline VECTOR GetPosition() { return m_vPos; }
	inline void GetPosition(VECTOR &vPos) {  vPos = m_vPos; }
	inline void GetNextPosVec(VECTOR& vPos) { vPos = m_vNextPos; }

	//Y軸角度取得
	inline VECTOR GetRotate() { return m_vRot; }
	//半径取得
	inline float GetRadius() { return PLAYER_RADIUS; }

	tagPlayerState GetPlayerState()			{ return m_eState; }	//プレイヤーの状態を取得
	void GetHalfSize(VECTOR& vHalfSize);							//半分のサイズを取得
	void GetSpd(VECTOR& vSpd)				{ vSpd = m_vSpd; }		//プレイヤーの速さを取得
  VECTOR GetSpd()							{ return m_vSpd; }		//プレイヤーの速さを取得
	void GetCenterPos(VECTOR& vPos);								//プレイヤーの中心座標を設定
	void GetSize(VECTOR& vSize);									//縦、横、奥行きのサイズ取得

	//物体にあっているかどうか
	bool SetIsHit(bool flag) { return m_IsHit = flag; }	
	bool SetIsHitSide(bool flag) { return m_IsHitSide = flag; }
	bool SetIsHitLength(bool flag) { return m_IsHitLength = flag; }

	//生存フラグの設定・取得
	void SetIsAllive(bool flag) { m_IsAllive = flag; }			//生存フラグの設定
	bool GetIsAllive() { return m_IsAllive; }					//生存フラグの取得

	//ジャンプフラグ取得・設定
	void SetIsJamp(bool flag) { m_IsJump = flag; }				//ジャンプフラグ設定
	bool GetIsJamp() { return m_IsJump; }						//ジャンプフラグ取得

private:
	//何もしていないときの処理
	void ExecDefault();
	//歩き中
	void ExecWalk();
	//走り中
	void ExecRun();
	////待機中
	//void ExecWait();
	////くねくね中
	//void ExecUpDown();
	////手を振る
	//void ExecShake();
	////ピアノ？
	//void ExecPiano();
	////ダンス中
	//void ExecDance();
};
