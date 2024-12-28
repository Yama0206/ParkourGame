#pragma once

#include "Dxlib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../shot/ShotManager.h"
#include "../Model/Model.h"
#include "../Math/Math.h"
#include "../Input/Pad/Pad.h"
#include "../Camera/CameraManager.h"
#include "../Debug/DebugManager.h"

static const char PLAYER_MODEL_PATH[]	
= { "data/char/Player.mv1" };								//ロードするファイル名
static const float PLAYER_RADIUS = 2.5f;					//プレイヤーの半径

static constexpr float PLAYER_WIDTH = 10.0f;					//プレイヤーの横サイズ
static constexpr float PLAYER_HEIGHT = 18.0f;					//プレイヤーの縦サイズ
static constexpr float PLAYER_DEPTH = 10.0f;					//プレイヤーの奥行き
static constexpr float PLAYER_HALF_HEIGHT = 9.0f;				//プレイヤーの高さの半分の大きさ
static constexpr float PLAYER_HALF_WIDHT = 5.0f;				//プレイヤーの横幅の半分の大きさ
static constexpr int   PLAYER_DIR_NUM = 6;						//プレイヤーの向きの数

class CPlayer : public CModel
{
private:
	//アニメーション一覧
	enum tagAnim {
		ANIMID_WAIT,			//ぶらぶら
		ANIMID_RUN,				//小走りモーション
		ANIMID_FAST_RUN,		//走りモーション
		ANIMID_RUNNINGJUMP,		//走りジャンプモーション
		ANIMID_JUMP,			//ジャンプモーション
		ANIMID_DIVINGJUMP,		//ダイビングジャンプモーション
		ANIMID_TPOSE,			//Ｔポーズ
		ANIMID_UPDOWN,			//くねくね上下
		ANIMID_SHAKE,			//手を振る
		ANIMID_PIANO,			//ピアノを引いて要るっぽい
		ANIMID_DANCE,			//踊ってる
		ANIMID_DEFAULT,			//デフォルトモーション
		ANIMID_HIDE,			//隠れてる

		ANIMID_NUM				//全アニメーション数
	};

	//向いている方向
	enum tagDir {
		UP = 0,		//上方向
		DOWN,		//下方向
		LEFT,		//左方向
		RIGHT,		//右方向
		FRONT,		//前方
		BACK,		//後方
	
	};

	tagDir m_eDir;					//プレイヤーの方向

	int m_PadXBuf;					//パッドレバーの左右の入力状態を格納する変数
	int m_PadYBuf;					//パッドレバーの上下の入力状態を格納する変数
	
	float m_fChangeRot;				//プレイヤーの方向を少しずつ回転させる用の変数
	float m_fRot;					//回転値
	float m_fGravity;				//プレイヤーの重力

	//フラグ
	bool m_bIsHit;					//プレイヤーが物体に当たっているかどうか
	bool m_bIsHitSide;				//プレイヤーが物体と横方向で当たった時
	bool m_bIsHitLength;			//プレイヤーが物体と縦方向で当たった時
	bool m_bIsGround;				//プレイヤーが地面についたかどうか
	bool m_bIsKeyHit;				//キーを押したかどうか
	bool m_bIsHitHideObject;		//隠れるようのオブジェクトとあたったかどうか
	bool m_bIsHide;					//ハイドモードかどうかを返す
	bool m_bIsParkourObject;		//パルクールオブジェクトにあたったかどうか
	bool m_bIsPlayAnimation;		//アニメーションを再生したかどうか
	bool m_bIsSpecifiedPos;			//指定の場所に来たかどうか
	bool m_bIsJump;					//ジャンプしたかどうか

	//パルクールオブジェクト4方向フラグ
	

public:
	//コンストラクタ
	CPlayer();
	~CPlayer();
	float m_fMoveSpeed;				//プレイヤーのスピード

public:
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
	void Jamp(VECTOR vRot);
	//データ関連の破棄
	void Delete();
	//終了処理
	void Fin();

public:
	//フラグ
	//生存フラグの設定・取得
	void SetIsAllive(bool bflag) { m_IsAllive = bflag; }						//生存フラグの設定
	bool GetIsAllive() { return m_IsAllive; }									//生存フラグの取得

	//ジャンプフラグ取得・設定
	void SetIsJamp(bool bflag) { m_bIsGround = bflag; }							//ジャンプフラグ設定
	bool GetIsJamp() { return m_bIsGround; }										//ジャンプフラグ取得

	//隠れるようオブジェクトと当たったかどうか
	void SetIsHitHideObject(bool bflag) { m_bIsHitHideObject = bflag; }			//隠れるようのオブジェクトとあたったかどうかフラグ設定
	bool GetIsHitHideObject()			{ return m_bIsHitHideObject; }			//隠れるようのオブジェクトとあたったかどうかフラグ取得

	//ハイドモードかどうか
	bool GetIsHide()					{ return m_bIsHide; }					//ハイドモード取得

public:
	//キーボード操作
	void Control_KeyBord(VECTOR vRot);
	//当たった分戻す
	void ReflectCollision(VECTOR vAddVec);
	//左スティックの角度にあわせてプレイヤーを回転させる
	void PadRotation(VECTOR vCameraRot);
	//移動ベクトル
	void CalcMoveVec(VECTOR vCameraRot);
	//座標に移動量を加算
	void AddMove();


	float Camera, Player;
public:
	//状態ごとの処理
	//待機
	void WaitCalc();
	//小走り
	void RunCalc();
	//ダッシュ
	void FastRunCalc();
	//ジャンプ
	void JumpCalc();
	//ダイビングジャンプ
	void DivingJumpCalc();

	//重力計算
	void Gravity();
	//パルクール重力
	void ParkourGravity();


public:
	//指定の場所に移動
	VECTOR MoveIocationSpecification(VECTOR _startPos, VECTOR _endPos);

	//指定の場所を向く
	VECTOR RotetoSpecifiedPos(VECTOR vEndPos, VECTOR vStartPos, VECTOR& vRot, VECTOR vSpd, float RotetoSpd);

public:
	//パルクール
	void ParkourMotion(VECTOR vPos,float Gravity);

	//パルクール始め
	void ParkourBegin(VECTOR vStartPos, VECTOR vSpd);
	//パルクール途中
	void ParkourMiddle(VECTOR ObjectPos);
	//パルクール終了
	void ParkourFin();

public:
	//コントローラー操作//
	//すべての状態で使える操作
	void PadControl_AllState();
	//小走り操作
	void PadControl_Run();
	//ダッシュジャンプ操作


	////キーボード操作
	//void KeyBordControl_Default();
	//void KeyBordControl_Run();
	//void KeyBordControl_FastRun();
	//void KeyBordControl_Jump();

public:
	//取得
	//進んでいる方向チェック
	void GetMoveDir(bool* _DirArray);	
	//方向を変える
	void ChangeDir(int FreamCnt);

	//座標取得
	inline VECTOR	GetPosition()					{ return m_vPos; }			//プレイヤーの座標
	inline VECTOR	GetNextPosVec()					{ return m_vNextPos; }		//プレイヤーの移動後の座標
	inline void		GetPosition(VECTOR &vPos)		{  vPos = m_vPos; }			//プレイヤーの座標
	inline void		GetNextPosVec(VECTOR& vPos)		{ vPos = m_vNextPos; }		//プレイヤーの移動後の座標


	//Y軸角度取得
	inline VECTOR	GetRotate() { return m_vRot; }
	inline VECTOR	GerViwPoint() { return m_vRot; }

	//半径取得
	inline float	GetRadius() { return PLAYER_RADIUS; }

	void			GetHalfSize(VECTOR& vHalfSize)		{ vHalfSize = DivVec(m_vSize, 2.0f); }								//半分のサイズを取得
	VECTOR			GetSpd()							{ return m_vSpd; }													//プレイヤーの速さを取得
	float			GetfSpd()							{ return m_fMoveSpeed; }											//スピードを取得(float)
	void			GetSize(VECTOR& vSize)				{ vSize = m_vSize; }												//縦、横、奥行きのサイズ取得
	void			GetCenterPos(VECTOR& vPos)			{ vPos = VAdd(m_vPos, VGet(0.0f, PLAYER_HALF_HEIGHT, 0.0f)); }		//プレイヤーの中心座標を設定
	VECTOR			GetForcsPos();																							//プレイヤーカメラに渡す注視点座標

	//設定
public:
	//座標設定
	void SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void SetPosX(float vPosX);								//X座標
	void SetPosY(float vPosY);								//Y座標
	void SetPosZ(float vPosZ);								//Z座標
	void SetNextPosVec(VECTOR vPos) { m_vNextPos = vPos; }	//移動後の座標
	void SetNextPosX(float vNextPosX);						//移動後のX座標
	void SetNextPosY(float vNextPosY);						//移動後のY座標
	void SetNextPosZ(float vNextosZ);						//移動後のZ座標
	//サイズ設定
	VECTOR SetSize();
		
	//物体にあっているかどうか
	void SetIsHit(bool flag)					{  m_bIsHit = flag; }	
	void SetIsHitSide(bool flag)				{  m_bIsHitSide = flag; }
	void SetIsHitLength(bool flag)				{  m_bIsHitLength = flag; }
	void SetIsHitParkourObject(bool flag)		{ m_bIsParkourObject = flag; }
	
	//速さ初期化
	void RessetSpeed();

private:
	//状態ごとの処理
	//デフォルトの処理
	void ExecDefault();
	//何もしていない時
	void ExecWait(VECTOR vRot);
	//歩き中
	void ExecRun(VECTOR vRot);
	//走り中
	void ExecFastRun(VECTOR vRot);
	//ジャンプ
	void ExecJump(VECTOR vRot);
	//ダッシュジャンプ
	void ExecRunningJump(VECTOR vRot);
	//ダイビングジャンプ
	void ExecDivingJump();
	//ハイドモード
	void ExecHide();
	////くねくね中
	//void ExecUpDown();
	////手を振る
	//void ExecShake();
	////ピアノ？
	//void ExecPiano();
	////ダンス中
	//void ExecDance();
};
