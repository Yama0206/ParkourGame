#include "Enemy.h"
#include <math.h>

//定義
const int ENEMY_CP_MAX = 4;					//チェックポイントの数
constexpr int ENEMY_TRAKINGAREA = 200;		//敵がプレイヤーを追跡する範囲

//コンストラクタ
CEnemy::CEnemy()
{
	//ひとまず初期化しておく
	memset(&m_vPos, 0, sizeof(VECTOR));
	memset(&m_vSpeed, 0, sizeof(VECTOR));
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSize, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));

	m_iHndl = -1;
	m_IsAllive = false;
	m_iNextCheckPointNum = 0;
	m_iLastPassedCP = -1;
	m_fRad = 5;
	m_fTrackingRad = ENEMY_TRAKINGAREA;
	m_eState = Patrol;
	m_eOldState = Patrol;

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
	memset(&m_vRot, 0, sizeof(VECTOR));
	memset(&m_vSize, 0, sizeof(VECTOR));
	memset(&m_vScale, 0, sizeof(VECTOR));

	m_iHndl = -1;
	m_IsAllive = false;
	m_iNextCheckPointNum = 0;
	m_iLastPassedCP = -1;
	m_fRad = 5;
	m_fTrackingRad = ENEMY_TRAKINGAREA;
	m_eState = Patrol;
	m_eOldState = Patrol;

	FrameCnt = 0;
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
		MV1SetScale(m_iHndl, m_vScale);
	}
}

void CEnemy::Draw()
{
	if (m_IsAllive)
	{
		MV1DrawModel(m_iHndl);
		DrawFormatString(500, 32, GetColor(255, 0, 0), "%f,%f,%f", m_vPos.x, m_vPos.y, m_vPos.z);
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step()
{
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

	m_vPos.x += sinf(m_vRot.y) * -m_vSpeed.x;
	m_vPos.z += cosf(m_vRot.y) * -m_vSpeed.z;

}

void CEnemy::TrackingCheckPoint(int Index)
{
	//ホーミング処理
	VECTOR CheckPosVec;
	//敵からチェックポイント向かうベクトル
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(Index).x - m_vPos.x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(Index).z - m_vPos.z;

	float fCrossZ = 0.0f;

	//現在の進行方向のベクトル
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(m_vRot.y) * -1.0f;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(m_vRot.y) * -1.0f;

	//2つのベクトルの外積を計算
	fCrossZ = CheckPosVec.x * MoveVec.z - MoveVec.x * CheckPosVec.z;

	//fCrossZの計算結果で左右の判定を行う
	if (fCrossZ > 0)
	{
		m_vRot.y += 0.1;
	}
	else if (fCrossZ < 0)
	{
		m_vRot.y -= 0.1;
	}

	m_vPos.x += sinf(m_vRot.y) * -m_vSpeed.x;
	m_vPos.z += cosf(m_vRot.y) * -m_vSpeed.z;
}


//リクエスト
bool CEnemy::RequestEnemy(const VECTOR& vPos, const VECTOR& vSpeed)
{
	//すでに描画されている
	if (m_IsAllive)return false;

	m_vPos = vPos;
	m_vSpeed = vSpeed;
	m_IsAllive = true;

	//1度座標更新をしておく
	MV1SetPosition(m_iHndl, m_vPos);
	return true;
}

void CEnemy::Update()
{
	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}

//当たり判定後の処理
void CEnemy::HitCalc()
{
	CSoundManager::Play(CSoundManager::SOUNDID_SE_EXPLONE);
	//とりあえずフラグを消すだけ
	m_IsAllive = false;
}

//情報の設定
void CEnemy::SetInfo(VECTOR vPos, VECTOR vSpeed, VECTOR vScale, VECTOR vRot, bool IsFrag)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSpeed = vSpeed;
	m_vScale = vScale;
	m_IsAllive = IsFrag;
}