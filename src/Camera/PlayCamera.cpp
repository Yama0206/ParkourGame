#include "PlayCamera.h"
#include <iostream>

using namespace std;

//定義関連
const float VIEWPOINT_SPEED = 0.05f;								//視点移動時の速さ
constexpr float INCLINE_STICK_RATE = 0.1f;							//スティックを傾けたときの何%倒したか
constexpr float STICK_MAX_VALUE = 1000.0f;							//スティックを傾けたときの最大値

//コンストラクタ
CPlayerCamera::CPlayerCamera()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vForcus, 0.0f, sizeof(VECTOR));
	memset(&m_vUp, 0.0f, sizeof(VECTOR));
	memset(&m_vRot, 0.0f, sizeof(VECTOR));
}

CPlayerCamera::~CPlayerCamera() {}

//初期化
void CPlayerCamera::Init()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vForcus, 0.0f, sizeof(VECTOR));
	memset(&m_vUp, 0.0f, sizeof(VECTOR));
	memset(&m_vRot, 0.0f, sizeof(VECTOR));
	
	m_MousePosX = 0;
	m_MousePosY = 0;
}

void CPlayerCamera::Init(VECTOR vCameraPos, VECTOR vForcusPos, VECTOR vUP)
{
	m_vPos = vCameraPos;
	m_vForcus = vForcusPos;
	m_vUp = vUP;
}

//カメラの毎回呼ぶ処理
void CPlayerCamera::Step(VECTOR vForcus, VECTOR vSpd)
{
	//カメラの視点移動操作
	ViewControl();

	//注視点の設定
	m_vForcus = vForcus;

	//カメラ用の行列
	MATRIX MoveMatrix;		//平行移動行列
	MATRIX PosMatrix;		//元の位置に戻す行列
	MATRIX RevMatrix;		//原点に移動する行列
	MATRIX Matrix;			//行列の合成をした値をいれる行列

	//カメラの座標を決める
	VECTOR vCameraPos = VAdd(vForcus, VGet(0.0f, CAMERA_OFFSET_Y, -CAMERA_LENGTH));

	MoveMatrix.m[3][3] = 1.0f;
	PosMatrix.m[3][3] = 1.0f;
	RevMatrix.m[3][3] = 1.0f;
	Matrix.m[3][3] = 1.0f;

	//行列に値を代入
	MoveMatrix = MGetTranslate(vSpd);									//移動行列
	PosMatrix = MGetTranslate(vForcus);									//座標の行列
	RevMatrix = MGetTranslate(VScale(vForcus, -1));						//座標の反対行列

	//Y軸回転行列の作成
	//引数はラジアン値
	MATRIX YRot = MGetRotY(m_vRot.y);		//Y軸回転
	MATRIX XRot = MGetRotX(m_vRot.x);		//X軸回転

	//行列の合成
	// 動作させたい順番で掛け算していい
	//①移動行列×②Y軸回転
	Matrix = MMult(RevMatrix, XRot);
	Matrix = MMult(Matrix, YRot);
	Matrix = MMult(Matrix, PosMatrix);

	//行列の座標変換
	m_vPos = VTransform(vCameraPos, Matrix);
}

//視点操作
void CPlayerCamera::ViewControl()
{
	//パッドの状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &m_JoyState);

	//1F前の回転値を入れておく
	m_vRot = m_vOldRot;

	//X方向にどこまで回転させるか決める
	//角度をラジアンに変換
	float MaxRotX = TransAngleToRadian(73.0f);

	//キャラクターのカメラの回転
	// パッド
	//右スティックの感度
	RightStickSensitivity(m_JoyState);


	// キーボード
	if (CInput::IsKeyKeep(KEY_INPUT_RIGHT))
	{
		m_vRot.y += VIEWPOINT_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_LEFT))
	{
		m_vRot.y -= VIEWPOINT_SPEED;
	}
	if (CInput::IsKeyKeep(KEY_INPUT_UP) && fabs(m_vRot.x) < MaxRotX)
	{
		m_vRot.x += -VIEWPOINT_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_DOWN) && fabs(m_vRot.x) < MaxRotX)
	{
		m_vRot.x += VIEWPOINT_SPEED;
	}

	if (fabs(m_vRot.x) >= MaxRotX)
	{
		m_vRot = m_vOldRot;
	}

}

void CPlayerCamera::RightStickSensitivity(DINPUT_JOYSTATE JoyState)
{
	//JoyPad
	//左右
	m_vRot.y += VIEWPOINT_SPEED * (JoyState.Rx / 1000.0f);
	//上下
	m_vRot.x += VIEWPOINT_SPEED * (JoyState.Ry / 1000.0f);	

	//DUALSHOCK4
	////左右
	//m_vRot.y += VIEWPOINT_SPEED * (JoyState.Z / 1000.0f);
	////上下
	//m_vRot.x += VIEWPOINT_SPEED * (JoyState.Rz / 1000.0f);

}

//更新したデータを反映
void CPlayerCamera::UpDate()
{
	//1F前の回転値を更新
	m_vOldRot = m_vRot;

	//カメラを更新
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vForcus, m_vUp);
}