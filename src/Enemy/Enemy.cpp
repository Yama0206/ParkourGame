#include "Enemy.h"
#include <math.h>

//定義
constexpr int ENEMY_CP_MAX = 4;						//チェックポイントの数
constexpr int ENEMY_SEARCH_AREA = 200;				//敵がプレイヤーを索敵する範囲
constexpr int ENEMY_TRACKING_AREA = 300;			//敵がプレイヤーを追いかける範囲
constexpr int ENEMY_TRACKING_PALYER_AREA = 50;		//敵がプレイヤーを直接追いかける

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
	m_fTrackingRad = ENEMY_TRACKING_AREA;
	m_fSearchRad = ENEMY_SEARCH_AREA;
	m_fTrackingPlayerRad = ENEMY_TRACKING_PALYER_AREA;
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
	m_fTrackingRad = ENEMY_TRACKING_AREA;
	m_fSearchRad = ENEMY_SEARCH_AREA;
	m_fTrackingPlayerRad = ENEMY_TRACKING_PALYER_AREA;
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
#ifdef MY_DEBUG
		VECTOR vPos = m_vPos;
		vPos.y += m_fRadius;
		DrawSphere3D(vPos, m_fRadius, 16, GetColor(0, 0, 255), GetColor(0, 0, 0), FALSE);
#endif
	}
}

void CEnemy::Step()
{
	CDebugManager::GetInstance()->AddFormatString(0,0,"敵の座標 = %f,%f,%f", m_vPos.x, m_vPos.y,m_vPos.z);
	CDebugManager::GetInstance()->AddFormatString(0,20,"今の状態 = %d",m_eState);
	CDebugManager::GetInstance()->AddFormatString(0,40,"1F前の状態 = %d",m_eOldState);
	CDebugManager::GetInstance()->AddFormatString(0, 60, "次に向かうチェックポイントの番号 = %d", m_iNextCheckPointNum);
	CDebugManager::GetInstance()->AddFormatString(0, 80, "最後に通ったチェックポイントの番号 = %d",m_iLastPassedCP);
	CDebugManager::GetInstance()->AddFormatString(0, 100, "索敵範囲 = %f", m_fSearchRad);
	CDebugManager::GetInstance()->AddFormatString(0, 120, "プレイヤー追跡範囲 = %f", m_fTrackingPlayerRad);


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

void CEnemy::TrackingCheckPoint(int CheckPointIndex)
{
	//ホーミング処理
	VECTOR CheckPosVec;
	//敵からチェックポイント向かうベクトル
	CheckPosVec.x = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).x - m_vPos.x;
	CheckPosVec.y = 0.0f;
	CheckPosVec.z = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex).z - m_vPos.z;

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

	m_vPos.x += sinf(m_vRot.y) * - m_vSpeed.x;
	m_vPos.z += cosf(m_vRot.y) * - m_vSpeed.z;
}

void CEnemy::NearCheckPointFind()
{
	VECTOR vPos, vComparePos;

	memset(&vPos, 0.0f, sizeof(vPos));
	memset(&vComparePos, 0.0f, sizeof(vComparePos));

	for (int i = 0; i < CCheckPointManager::GetInstance()->GetSize(); i++) {

		vComparePos = CCheckPointManager::GetInstance()->GetPosVec(i);
		vPos = CCheckPointManager::GetInstance()->GetPosVec(i);

		if (vPos.x < vComparePos.x || vPos.z < vComparePos.z)
		{
			m_iNextCheckPointNum = i;
		}
	}
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