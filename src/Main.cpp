//2309426_火山皓太 就職作品


#include "DxLib.h"				//DXライブラリのインクルード
#include "Input/Input.h"	
#include "Input/Pad/Pad.h"	
#include "Fps/Fps.h"
#include "Scene/SceneManager.h"
#include "CheckPoint/Manager/CheckPointManager.h"
#include "Debug/DebugManager.h"

// define
#define	SCREEN_SIZE_X	1280	// X方向の画面サイズを指定
#define	SCREEN_SIZE_Y	720	// Y方向の画面サイズを指定

const char BULLET_PATH[] = { "data/shot/plshot.x" };

// Win32アプリケーションは WinMain関数 から始まる
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// 画面サイズを変更
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//描画するスクリーンを設定する
	SetDrawScreen(DX_SCREEN_BACK);

	//Zバッファを使用する場合TRUE
	SetUseZBuffer3D(TRUE);
	
	//-----------------------------------------
	//一番最初に１回だけやる処理をここに書く
	
	//シーン
	SceneManager cSceneManager;

	//入力関連初期化
	CInput::InitInput();
	CPad::Init();

	 int iHndl = MV1LoadModel(BULLET_PATH);
	//-----------------------------------------

	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//エスケープキーが押されたら終了
			break;
		}

		//フレームレート制御
		FpsControll_Update();

		//画面に表示されたものを初期化
		ClearDrawScreen();

		//-----------------------------------------
		//ここからゲームの本体を書くことになる
		//-----------------------------------------
		
		//入力関連
		CInput::StepInput();
		CPad::Step();


		cSceneManager.Loop();
		cSceneManager.Draw();


		//Fps制御------------------------------
		InitFPS();							//FPSの初期化	
		CalcFPS();							//FPSの計算
		StepFPS();							//FPSの通常処理		
		DrawFPS();							//FPSの表示		
		SetNowTimeFps();					//現在の時間を設定		
		IsExecuteFPS();						//前回の実行から実行可能フレームかチェック	
		FpsControll_Wait();					//待機
		//-------------------------------------

		//-----------------------------------------
		//ループの終わりに
		//フリップ関数
		ScreenFlip();

	}

	//-----------------------------------------
	//最後に１回だけやる処理をここに書く
	//チェックポイントクラスを削除
	CCheckPointManager::DeleteInstance();
	CDebugManager::DeleteInstance();
	//-----------------------------------------
	//DXライブラリの後処理
	DxLib_End();

	return 0;
}

