#include "DebugCamera.h"
#include "../Input/Input.h"

// カメラの距離
#define CAMERA_LENGHT 30.0f

// 視点の高さ
#define CAMERA_OFFSET_Y 10.0f

// 注視点の高さ
#define FORCUS_OFFSET_Y 10.0f

// カメラの移動速度
#define CAMERA_MOVE_SPEED 1.0f

// カメラの回転速度
#define CAMERA_ROTATE_SPEED 0.02f

// コンストラクタ
CDebugCamera::CDebugCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vCameraRot, 0, sizeof(VECTOR));
}

// デストラクタ
CDebugCamera::~CDebugCamera() {}

// 初期化
void CDebugCamera::Init() {
	// 念のため初期値を設定
	m_vCameraPos = VGet(0.0f, 0.0f, 1.0f);
	m_vCameraRot = VGet(0.0f, 0.0f, 1.0f);
}

// 初期化
void CDebugCamera::Init(VECTOR vPos, float fRot) {
	m_vCameraPos = vPos;
	m_vCameraRot.y = fRot + DX_PI_F;
}

// 毎フレーム実行する処理
void CDebugCamera::Step() {
	// カメラの移動の操作
	VECTOR fSpd = { 0.0f, 0.0f, 0.0f };
	if (CheckHitKey(KEY_INPUT_W)) {
		fSpd.z = CAMERA_MOVE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		fSpd.z = -CAMERA_MOVE_SPEED;
	}
	float fRot = 0.0f;
	if (CheckHitKey(KEY_INPUT_A)) {
		fSpd.x = -CAMERA_MOVE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		fSpd.x = CAMERA_MOVE_SPEED;
	}
	if (CInput::IsKeyKeep(KEY_INPUT_E))
	{
		fSpd.y = CAMERA_MOVE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_Q))
	{
		fSpd.y = -CAMERA_MOVE_SPEED;
	}

	// カメラの向きの操作
	if (CheckHitKey(KEY_INPUT_UP)) {
		m_vCameraRot.x -= CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		m_vCameraRot.x += CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		m_vCameraRot.y -= CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		m_vCameraRot.y += CAMERA_ROTATE_SPEED;
	}

	MATRIX matrix1, matrix2, matrix3, matrix4;
	VECTOR vPos = VScale(m_vCameraPos, -1);

	matrix1.m[3][3] = 1.0f;
	matrix2.m[3][3] = 1.0f;
	matrix3.m[3][3] = 1.0f;
	matrix4.m[3][3] = 1.0f;

	matrix1 = MGetTranslate(fSpd);
	matrix2 = MGetTranslate(vPos);
	matrix3 = MGetTranslate(m_vCameraPos);

	//Y軸回転行列の作成
	//引数はラジアン値
	MATRIX YRot = MGetRotY(m_vCameraRot.y);
	MATRIX XRot = MGetRotX(m_vCameraRot.x);

	//行列の合成
	// 動作させたい順番で掛け算していい
	//①移動行列×②Y軸回転
	matrix4 = MMult(matrix2, matrix1);
	matrix4 = MMult(matrix4, XRot);
	matrix4 = MMult(matrix4, YRot);
	matrix4 = MMult(matrix4, matrix3);


	//行列の座標変換
	m_vCameraPos = VTransform(m_vCameraPos, matrix4);
}

// 描画
void CDebugCamera::Draw() {
	DrawString(0, 0, "デバッグカメラモード", GetColor(0, 255, 0));
}

// 更新したデータを反映
void CDebugCamera::Update() {
	SetCameraPositionAndAngle(m_vCameraPos, m_vCameraRot.x, m_vCameraRot.y, m_vCameraRot.z);
}