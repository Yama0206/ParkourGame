#pragma once
#include "DxLib.h"
#include "../shot/ShotManager.h"
#include "../System/Sound/SoundManager.h"

//定義
const float RADIUS = 5.0f;					//敵の半径				

class CEnemy
{
protected:
	VECTOR m_vPos;				//座標
	VECTOR m_vSpeed;			//移動速度
	VECTOR m_vRot;				//回転値
	VECTOR m_vSize;				//拡縮率

	int m_iHndl;				//モデルハンドル
	bool m_IsActive;			//生存フラグ
	float m_fRadius;			//半径

	int FrameCnt;				//フレームカウント

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
	void Step();
	//描画処理
	void Draw();

	//vPos		:		初期座標
	//vSpeed	:		移動速度(方向ベクトルで)
	//@return	:		true = リクエスト成功 false = 失敗
	bool RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed);

	//生存判定
	bool IsActiv() { return m_IsActive; }
	//座標取得
	// vPos		:	座標を保存する変数
	void GetPosition(VECTOR& vPos) { vPos = m_vPos; }
	float GetRadius() { return m_fRadius; }

	//情報の設定
	void SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vSize, VECTOR vRot);

	//当たり判定後の処理
	void HitCalc();
};


