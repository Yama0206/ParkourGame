#include "Enemy.h"
#include <math.h>

//コンストラクタ
CEnemy::CEnemy()
{
	//ひとまず初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_bIsActive = false;

	FrameCnt = 0;
}

//デストラクタ
CEnemy::~CEnemy()
{
	//本来は必要ないけど念のため
	Fin();
}

//初期化
void CEnemy::Init()
{
	//ひとまず初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	m_iHndl = -1;
	m_fRadius = RADIUS;
	m_bIsActive = false;
}

void CEnemy::Fin()
{
	//モデルハンドル解放
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//データロード
void CEnemy::Load(int iMdlHndl)
{
	if (m_iHndl == -1)
	{
		m_iHndl = MV1DuplicateModel(iMdlHndl);
		MV1SetScale(m_iHndl, VGet(5.0f, 5.0f, 5.0f));
	}
}

void CEnemy::Draw()
{
	if (m_bIsActive)
	{
		MV1DrawModel(m_iHndl);
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step()
{
	if (!m_bIsActive) return;

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//一定範囲を超えたら消す
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_bIsActive = false;
	}

	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}

//リクエスト
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに描画されている
	if (m_bIsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_bIsActive = true;

	//1度座標更新をしておく
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

//当たり判定後の処理
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//とりあえずフラグを消すだけ
	m_bIsActive = false;
}

//情報の設定
