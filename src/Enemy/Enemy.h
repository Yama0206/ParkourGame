#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"
#include "../Math/Math.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include "../CheckPoint/Manager/CheckPointManager.h"

//定義
const float RADIUS = 5.0f;					//敵の半径				

//敵の状態
enum EnemyState
{
	Patrol = 1,				//巡回
	TrackingCheckPoint,		//チェックポイントを追跡
	TrackingPlayer,			//プレイヤーを追跡
};


class CEnemy
{
protected:
	VECTOR m_vPos;					//座標
	VECTOR m_vSpeed;				//移動速度
	VECTOR m_vRot;					//回転値
	VECTOR m_vSize;					//縦　横　奥行きのサイズ
	VECTOR m_vScale;				//拡縮率

	int		m_iHndl;				//モデルハンドル
	bool	m_IsAllive;				//生存フラグ
	float	m_fRad;					//半径
	float	m_fTrackingRad;			//追従する半径
	float	m_fSearchRad;			//索敵範囲
	int		m_iNextCheckPointNum;	//次に向かうチェックポイントの番号
	int		m_iLastPassedCP;		//敵が通ったチェックポイント

	int FrameCnt;					//フレームカウント

	EnemyState m_eState;			//敵の状態
	EnemyState m_eOldState;			//敵の1F前の状態

public:

	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

public:
	//初期化
	void Init();

	//データロード
	void Load(int iMdlHndl);
	//終了処理
	void Fin();
	//毎フレーム呼ぶ処理
	void Step();
	//描画処理
	void Draw();
	//更新処理
	void Update();

	//vPos		:		初期座標
	//vSpeed	:		移動速度(方向ベクトルで)
	//@return	:		true = リクエスト成功 false = 失敗
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

public:
	//プレイヤーを追跡
	void TrackingPlayer(VECTOR vPlayerPos);
	//チェックポイント
	void TrackingCheckPoint(int Index);

public:
	//座標取得
	// 参照渡し
	// vPos		:	座標を保存する変数
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	
	//取得関数
	VECTOR		GetPosVec()					{ return m_vPos; }						//座標
	VECTOR		GetSizeVec()				{ return m_vSize; }						//大きさ
	VECTOR		GetSpeedVec()				{ return m_vSpeed; }					//速さ
	VECTOR		GetRotVec()					{ return m_vRot; }						//回転値
	int			GetNextCheckPointNum()		{ return m_iNextCheckPointNum; }		//次に向かうチェックポイント
	float		GetRadius()					{ return m_fRad; }						//半径
	float		GetTrackingRad()			{ return m_fTrackingRad; }				//追跡をする半径
	float		GetSearchRad()				{ return m_fSearchRad; }				//索敵をする半径
	int			GetLastPassedCheckPoint()	{ return m_iLastPassedCP; }				//最後に通ったチェックポイントの番号
	EnemyState	GetState()					{ return m_eState; }					//現在の状態
	EnemyState	GetOldState()				{ return m_eOldState; }					//1F前の状態
	//生存判定取得
	bool GetIsActiv() { return m_IsAllive; }

	//情報の設定
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot, bool IsFrag);	

	//設定関数
	void SetPosVec(VECTOR vPos)		{ m_vPos = vPos; }				//座標
	void SetSizeVec(VECTOR vSize)	{ m_vSize = vSize; }			//大きさ
	void SetSpeedVec(VECTOR vSpeed) { m_vSpeed = vSpeed; }			//速さ
	void SetRotVec(VECTOR vRot)		{ m_vRot = vRot; }				//回転値

	void SetPosVec_X(float fPos)	{ m_vPos.x = fPos; }			//X座標
	void SetPosVec_Y(float fPos)	{ m_vPos.y = fPos; }			//Y座標
	void SetPosVec_Z(float fPos)	{ m_vPos.z = fPos; }			//Z座標

	void SetRotVec_X(float fRot)	{ m_vRot.x = fRot; }			//X回転値
	void SetRotVec_Y(float fRot)	 { m_vRot.y = fRot; }			//Y回転値
	void SetRotVec_Z(float fRot)	{ m_vPos.z = fRot; }			//Z回転値

	//最後に通ったチェックポイントの番号
	void SetLastPassedCheckPoint(int Num) { m_iLastPassedCP = Num; }
	//次に向かうチェックポイントの番号を設定
	void SetNextCheckPointNum(int Num) { m_iNextCheckPointNum = Num; }

	//状態
	void SetState(EnemyState eState) { m_eState = eState; }				//現在
	void SetOldState(EnemyState eState) { m_eOldState = eState; }		//1F前

	//当たり判定後の処理
	void HitCalc();
};


