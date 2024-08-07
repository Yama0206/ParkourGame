#include "Shot.h"

//定義
const float RADIUS = 1.0f;				//半径

//コンストラクタ
CShot::CShot()
{
	//ひとまず初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_bIsActive = false;
}

//デストラクタ
CShot::~CShot()
{
	//本来は必要ないけど念のため
	Fin();
}

//初期化
void CShot::Init()
{
	//ひとまず初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_fRadius = RADIUS;
	m_bIsActive = false;
}

void CShot::Fin()
{
	//モデルハンドル解放
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//データロード
void CShot::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
	}
}

void CShot::Draw()
{
	if (m_bIsActive)
	{
		MV1DrawModel(m_iHndl);
	}
}

void CShot::Step()
{
	if (!m_bIsActive) return;

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//一定範囲を超えたら消す
	float fLength = 3000.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength)
	{
		m_bIsActive = false;
	}

	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}

//リクエスト
bool CShot::RequestShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに発射されている
	if (m_bIsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bIsActive = true;

	return true;
}

//当たり判定後の処理
void CShot::HitCalc()
{
	//とりあえずフラグを消すだけ
	m_bIsActive = false;
}

