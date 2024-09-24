#include "Field.h"

//初期化
void CField::Init()
{
	m_vPos = VGet(0.0f, -50.0f, 0.0f);
	m_vScale = { FIELD_X_SCALE, FIELD_Y_SCALE, FIELD_Z_SCALE };
	m_vSize = { FIELD_X_SIZE, FIELD_Y_SIZE, FIELD_Z_SIZE };

	m_iHndl = -1;						//画像ハンドル
}

//読み込み
void CField::Load()
{
	m_iHndl = MV1LoadModel(FIELD_PATH);

	//コリジョン情報構築
	MV1SetupCollInfo(m_iHndl);

}

//通常処理
void CField::Step() {}

//描画処理
void CField::Draw()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1DrawModel(m_iHndl);
}

//更新処理
VECTOR CField::HitCheck(VECTOR vCenter, float fRadius)
{
	VECTOR vOut = { 0.0f, 0.0f, 0.0f };			//物体が背景にめり込んだ距離
	m_IsHitFrag = false;

	MV1_COLL_RESULT_POLY_DIM res;		//あたり判定結果格納構造体
	res = MV1CollCheck_Sphere(m_iHndl, -1, vCenter, fRadius);

	//ヒットしていればフラグをtrueに
	for (int FieldIndex = 0; FieldIndex < res.HitNum; FieldIndex++)
	{
		//球の中心と最近点の座標の最短距離を計算
		VECTOR vSub = VSub(res.Dim[FieldIndex].HitPosition, vCenter);
		//めり込んだ距離を計算
		float len = VSize(vSub);
		//半径-中心と最近点の座標の最短距離
		len = fRadius - len;
		//法線ベクトルを計算する
		VECTOR vAns = VScale(res.Dim[FieldIndex].Normal, len);
		//めり込み量を加算
		vOut = VAdd(vOut, vAns);

		m_IsHitFrag = true;
	}
	MV1CollResultPolyDimTerminate(res);

	return vOut;
}

void CField::UpDate()
{
	MV1SetPosition(m_iHndl, m_vPos);
}

//終了処理
void CField::Fin()
{
	if (m_iHndl != -1)
	{
		MV1TerminateCollInfo(m_iHndl);		//コリジョン情報破棄
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}
