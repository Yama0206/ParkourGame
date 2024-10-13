#include "DxLib.h"
#include "Fps.h"
#include <math.h>

//フレームレート制御
static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;  //平均を取るサンプル数
static const int FPS = 60;  //設定したFPS


FrameRateInfo frameRateInfo = { 0 };

// FPS初期化処理
void InitFPS()
{
	// 現在の時間を、FPSの計算した時間に設定
	if (frameRateInfo.calcFpsTime == 0.0f) {
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}
}

// FPS更新処理
void SetNowTimeFps()
{
	// 現在の時間を取得
	frameRateInfo.currentTime = GetNowCount();
}

// FPS計算
void CalcFPS() {
	// 前回のFPSを計算した時間からの経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	// 前回のFPSを計算した時間から
	// 1秒以上経過していたらFPSを計算する
	if (difTime > 1000) {
		// フレーム回数をミリ秒に合わせる
		// 小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		// FPSを求める
		// 理想の数値は60000/1000で60となる
		frameRateInfo.fps = frameCount / difTime;

		// フレームレートカウントをクリア
		frameRateInfo.count = 0;

		// FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

// FPS表示（デバッグ用）
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1100, 50, color, "FPS[%.2f]", frameRateInfo.fps);
}

// 前回の実行から実行可能フレームかチェック
bool IsExecuteFPS()
{
	if (frameRateInfo.currentTime - frameRateInfo.lastFreamTime >= FRAME_TIME)
	{
		return true;
	}
	return false;
}

// FPSの通常処理
void StepFPS()
{
	// フレーム実行時の時間を更新
	frameRateInfo.lastFreamTime = frameRateInfo.currentTime;

	// フレーム数をカウント
	frameRateInfo.count++;
}


//フレームレートの制御


//初期化
void FpsControll_Initialize() {
	mStartTime = GetNowCount();
	mCount = 0;
	mFps = 0;
}

//FPS制御
bool FpsControll_Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void FpsControll_Wait() {
	int tookTime = GetNowCount() - mStartTime;  //かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;  //待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);  //待機
	}
}