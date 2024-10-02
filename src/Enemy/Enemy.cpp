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
	m_IsActive = false;

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
	m_IsActive = false;
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
	if (m_IsActive)
	{
		MV1DrawModel(m_iHndl);
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step(VECTOR vPlayerPos, VECTOR vPos, int Index)
{
	//敵の生存フラグがOFFの時中の処理を行わない
	if (!m_IsActive) return;
	
	//プレイヤーを追いかける
	TrackingPlayer(vPlayerPos);

	//チェックポイントに向かう
	//MoveCheckPoint(vPos, Index);

}

//プレイヤーを追跡する
void CEnemy::TrackingPlayer(VECTOR vPlayerPos)
{
	//ホーミング処理
	VECTOR PlayerVec;
	//敵からプレイヤーに向かうベクトル
	PlayerVec.x = vPlayerPos.x - m_vPos.x;
	PlayerVec.y = 0.0f;
	PlayerVec.z = vPlayerPos.z - m_vPos.z;

	float fCrossZ = 0.0f;

	//現在の進行方向のベクトル
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_vRot.y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_vRot.y) * -1.0f;

	//2つのベクトルの外積を計算
	fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

	//fCrossZの計算結果で左右の判定を行う
	if (fCrossZ > 0)
	{
		m_vRot.y += 0.1;
	}
	else if (fCrossZ < 0)
	{
		m_vRot.y -= 0.1;
	}

	m_vPos.x += sinf(m_vRot.y) * -0.3f;
	m_vPos.z += cosf(m_vRot.y) * -0.3f;

}

void CEnemy::TrackingCheckPoint()
{
	for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetCheckPointSize(); CheckPointIndex++) {
		//ホーミング処理
		VECTOR PlayerVec;
	
		//敵からプレイヤーに向かうベクトル
		PlayerVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x;
		PlayerVec.y = 0.0f;
		PlayerVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z;
		

		float fCrossZ = 0.0f;

		//現在の進行方向のベクトル
		VECTOR  MoveVec;

		memset(&MoveVec, 0.0f, sizeof(MoveVec));

		MoveVec.x = sinf(m_vRot.y) * -1.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = cosf(m_vRot.y) * -1.0f;

		//2つのベクトルの外積を計算
		fCrossZ = PlayerVec.x * MoveVec.z - MoveVec.x * PlayerVec.z;

		//fCrossZの計算結果で左右の判定を行う
		if (fCrossZ > 0)
		{
			m_vRot.y += 0.1;
		}
		else if (fCrossZ < 0)
		{
			m_vRot.y -= 0.1;
		}

		m_vPos.x += sinf(m_vRot.y) * -0.3f;
		m_vPos.z += cosf(m_vRot.y) * -0.3f;
	}
}

//リクエスト
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに描画されている
	if (m_IsActive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_IsActive = true;

	//1度座標更新をしておく
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

void CEnemy::Update()
{
	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}

//当たり判定後の処理
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//とりあえずフラグを消すだけ
	m_IsActive = false;
}

//情報の設定
void CEnemy::SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vScale, VECTOR vRot, bool IsActive)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSpeed = vSpeed;
	m_vSize = vScale;
	m_IsActive = IsActive;
}