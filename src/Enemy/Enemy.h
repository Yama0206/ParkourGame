#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"
#include "../Math/Math.h"
#include "../CheckPoint/Manager/CheckPointManager.h"

//定義
const float RADIUS = 5.0f;					//敵の半径				

//敵の状態
enum EnemyState
{
	Patrol = 1,		//巡回
	Tracking,		//追跡
};


class CEnemy
{
protected:
	VECTOR m_vPos;				//座標
	VECTOR m_vSpeed;			//移動速度
	VECTOR m_vRot;				//回転値
	VECTOR m_vSize;				//縦　横　奥行きのサイズ
	VECTOR m_vScale;			//拡縮率

	int m_iHndl;				//モデルハンドル
	bool m_IsActive;			//生存フラグ
	float m_fRadius;			//半径

	int FrameCnt;				//フレームカウント

	EnemyState m_eState;			//敵の状態

public:
	//コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

	//初期化
	void Init();

	//データロード
	void Load(int iMdlHndl);
	//終了処理
	void Fin();
	//毎フレーム呼ぶ処理
	void Step(VECTOR vPlayerPos);
	//描画処理
	void Draw();

	void TrackingPlayer(VECTOR vPlayerPos);

	//vPos		:		初期座標
	//vSpeed	:		移動速度(方向ベクトルで)
	//@return	:		true = リクエスト成功 false = 失敗
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//生存判定
	bool IsActiv() { return m_IsActive; }
	//座標取得
	// 参照渡し
	// vPos		:	座標を保存する変数
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }

	//戻り値
	VECTOR GetPosVec() { return m_vPos; }
	VECTOR GetRotVec() { return m_vRot; }
	float GetRadius() { return m_fRadius; }

	//情報の設定
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot, bool IsActive);
	void SetPosVec(VECTOR vPos) { m_vPos = vPos; }
	void SetRotVec(VECTOR vRot) { m_vRot = vRot; }

	void SetPosVec_X(float fPos) { m_vPos.x = fPos; }
	void SetPosVec_Y(float fPos) { m_vPos.y = fPos; }
	void SetPosVec_Z(float fPos) { m_vPos.z = fPos; }

	void SetRotVec_X(float fRot) { m_vRot.x = fRot; }
	void SetRotVec_Y(float fRot) { m_vRot.y = fRot; }
	void SetRotVec_Z(float fRot) { m_vPos.z = fRot; }

	//更新処理
	void Update();

	//当たり判定後の処理
	void HitCalc();
};


