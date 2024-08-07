#pragma once
#include <DxLib.h>

class CShot
{
private:
	VECTOR m_vPos;				//座標
	VECTOR m_vSpeed;			//移動速度
	int m_iHndl;				//モデルハンドル
	float m_fRadius;				//半径

	bool m_bIsActive;			//生存フラグ

public:
	//コンストラクタ・デストラクタ
	CShot();
	~CShot();

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
	bool RequestShot(const VECTOR& vPos, const VECTOR& vSpeed);
	//生存判定
	bool IsActiv() { return m_bIsActive; }

	//座標取得
	void GetPotision(VECTOR& vPos) { vPos = m_vPos; }
	//半径取得
	float GetRadius() { return m_fRadius; }

	//当たり判定後の処理
	void HitCalc();
};
