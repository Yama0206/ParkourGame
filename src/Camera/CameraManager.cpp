#include "CameraManager.h"

//定義関連
//基本となる視点・注視店・アップベクトル
static const VECTOR DEFAULT_EYE_POS = { 0.0f,  10.0f, -20.0f };
static const VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };

static const float ROTATE_DEBUG_SPEED = 0.1f;						//デバッグカメラの回転速度
static const float CAMERA_MOVE_SPEED = 1.0f;						//デバッグカメラの移動速度

//コンストラクタ
CCameraManager::CCameraManager()
{
	//ひとまず初期はゲームカメラを
	m_eCurrentCameraID = CAMERA_ID_PLAY;
	m_vPlayerRotateY = 0.0f;
}

//デストラクタ
CCameraManager::~CCameraManager(){}

//初期化
void CCameraManager::Init()
{
	m_cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);		//プレイヤー
	m_cDebugCam.Init(DEFAULT_EYE_POS);											//デバッグ
}

//初期化
void CCameraManager::Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp)
{
	m_cPlayCam.Init(vPos, vForcus, vUp);
	m_cDebugCam.Init(vPos);
}

//毎フレーム呼ぶ処理
void CCameraManager::Step(VECTOR vForcus, VECTOR vSpd){
	//カメラのタイプに合わせて、更新処理を変更する
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_cPlayCam.Step(vForcus, vSpd);
		m_cPlayCam.UpDate();
		break;
	case CAMERA_ID_DEBUG:
		m_cDebugCam.Step();
		m_cDebugCam.Update();
		break;
	}
}


// 描画
void CCameraManager::Draw() {
	switch (m_eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Draw();
	default:
		break;
	}
}

//カメラのニア・ファーの設定
void CCameraManager::SetNearFar(float fNear, float fFar)
{
	SetCameraNearFar(fNear, fFar);
}

// カメラタイプ変更
void CCameraManager::ChangeCamera(tagCAMERA_ID ID) {
	// ID変更
	m_eCurrentCameraID = ID;

	// 変更後にカメラを初期化
	switch (m_eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		// デバッグカメラ初期化
		m_cDebugCam.Init(m_cPlayCam.GetPosVEC(), m_vPlayerRotateY);
	default:
		break;
	}

	return;
}

//プレイヤーの角度を保存
void CCameraManager::SetPlayerRot(float vRot){
	m_vPlayerRotateY = vRot;
}

//終了処理
void CCameraManager::Fin()
{
}
