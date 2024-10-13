#pragma once

#define DEF_FPSCONTROLL_H


//設定フレームレート
#define FRAME_RATE	(60)

//1フレームの時間（ミリ秒）
#define FRAME_TIME	(1000 / FRAME_RATE)

//フレームレート情報
struct FrameRateInfo
{
	int currentTime;	//現在の時間
	int lastFreamTime;	//前回のフレーム実行時の時間
	int count;			//フレームカウント用
	int calcFpsTime;	//FPSを計算した時間
	float fps;			//計測したFPS（表示用）	
};


// FPS初期化処理
void InitFPS();

//FPS計算
void CalcFPS();

//FPS表示（デバッグ用）
void DrawFPS();

//現在の時間を設定
void SetNowTimeFps();

// 前回の実行から実行可能フレームかチェック
bool IsExecuteFPS();

// FPSの通常処理
void StepFPS();


//フレーレートの制御
void FpsControll_Initialize();

//FPS制御
bool FpsControll_Update();

//FPS表示
void FpsControll_Draw();

void FpsControll_Wait();