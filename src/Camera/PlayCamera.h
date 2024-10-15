#pragma once
#include "DxLib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../Math/Math.h"
#include "../Debug/DebugManager.h"

const float CAMERA_LENGTH = 50.0f;								//カメラの距離
const float CAMERA_OFFSET_Y = 50.0f;							//カメラの視点の高さ
const float FORCUS_OFFSET_Y = 10.0f;							//カメラの注視点の高さ
static const VECTOR CAMERA_SIZE = VGet(5.0f, 5.0f, 5.0f);		//カメラのサイズ

class CPlayerCamera
{
private:
	VECTOR m_vPos;					//視点
	VECTOR m_vForcus;				//注視点
	VECTOR m_vRot;					//回転値
	VECTOR m_vOldRot;				//1F前の回転値
	VECTOR m_vUp;					//上方向

	DINPUT_JOYSTATE m_JoyState;		//パッドの状態

	int* m_MousePosX, * m_MousePosY;	//マウスの座標

public:
	//コンストラクタ
	CPlayerCamera();
	~CPlayerCamera();

	//初期化
	void Init();
	void Init(VECTOR vCameraPos, VECTOR vForcusPos, VECTOR vUP);

	//カメラ座標取得
	VECTOR GetPosVEC()		 { return m_vPos; }				//視点
	VECTOR GetForcusPosVEC() { return m_vForcus; }			//注視点
	VECTOR GetUpVEC()		 { return m_vUp; }				//上方向
	VECTOR GetRot()			 { return m_vRot; }				//回転値

	//カメラの毎回呼ぶ処理
	//第1引数
	void Step(VECTOR vForcus, VECTOR vSpd);

	//視点操作
	void ViewControl();

	//カメラ情報の更新
	void UpDate();
};
