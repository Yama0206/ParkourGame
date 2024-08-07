#pragma once
#include "PlayCamera.h"
#include "DxLib.h"
#include "../Camera/DebugCamera.h"

class CCameraManager
{
public:
	//カメラのタイプ
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,				//ゲーム中のカメラ
		CAMERA_ID_DEBUG,			//デバッグ用のカメラ(今後制作)

		CAMERA_ID_NUM
	};

private:
	CPlayerCamera m_cPlayCam;					//プレイヤーカメラ
	CDebugCamera m_cDebugCam;					//デバッグ用カメラ
	tagCAMERA_ID m_eCurrentCameraID;			//現在のカメラ

	float		 m_vPlayerRotateY;				// プレイヤーの角度

public:
	//コンストラクタ・デストラクタ
	CCameraManager();
	~CCameraManager();

	//初期化
	// @vPos		:	視点
	// @vForcus		:	注視点
	// @vUp			:	上方向
	void Init();
	void Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp);

	//第1引数, カメラのニア		//第2引数, カメラのファー	
	void SetNearFar(float fNear, float fFar);

	//更新処理
	void Step(VECTOR vForcus, VECTOR vSpd);

	// 描画
	void Draw();

	//カメラタイプ変更
	void ChangeCamera(tagCAMERA_ID ID);

	//現在のカメラタイプを取得
	tagCAMERA_ID GetCameraID() { return m_eCurrentCameraID; }

	//プレイヤーの角度を保存
	void SetPlayerRot(float vRot);
	VECTOR GetPlayCamRot() { return m_cPlayCam.GetRot(); }

	//終了処理
	void Fin();
};




