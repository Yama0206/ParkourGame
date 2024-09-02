#pragma once
#include "DxLib.h"

#define KEY_BUF_LEN		(256)
#define MOUSE_BUF_LEN	(5)
#define PAD_BUF_LEN		(256)

enum JoyPadKey
{
	INPUT_DOWN = 1,
	INPUT_LEFT = 10, 
	INPUT_RIGHT = 20,
	INPUT_UP = 30,
	INPUT_1 = 40,
	INPUT_2 = 50,
	INPUT_3 = 60,
	INPUT_4 = 70,
	INPUT_5 = 80,
	INPUT_6 = 90,
	INPUT_7 = 100,
	INPUT_8 = 110,
	INPUT_9 = 120,
	INPUT_10 = 130,
};

static class CInput {
private:
	//現在のフレームのキー情報
	static char currentKeyBuf[KEY_BUF_LEN];
	//前フレームのキー情報
	static char preKeyBuf[KEY_BUF_LEN];

	//現在のフレームのPad情報
	static char currentPadBuf[PAD_BUF_LEN];
	//前フレームのPad情報
	static char prePadBuf[PAD_BUF_LEN];

	//現在のフレームのマウス情報
	static int currentMouseBuf[MOUSE_BUF_LEN];
	//前フレームのマウス情報
	static int preMouseBuf[MOUSE_BUF_LEN];

	static int JoypadNum;
public:
	//何を入力されたか
	static const int MOUSE_LEFT = 0;
	static const int MOUSE_RIGHT = 1;
	static const int MOUSE_MIDLE = 2;

	//入力制御初期化
	static void InitInput();

	//入力制御ステップ
	//ほかのStepより早く呼ぶ
	static void StepInput();
	static void StepInputPad();


	//キーボード関連
	//今押された
	static bool IsKeyPush(int key_code);
	//押し続ける
	static bool IsKeyKeep(int key_code);
	//離したとき
	static bool IsKeyRelease(int key_code);

	static bool IsKeyDown(int key_code);

	//Pad関連
	//今押された
	static bool IsPadPush(int key_code);
	//押し続ける
	static bool IsPadKeep(int key_code);
	//離したとき
	static bool IsPadRelease(int key_code);
	//押されたかどうか
	static bool IsPadDown(int key_code);

	//パッドの入力状態を得る
	static void GetHitPadStateAll();

	//マウス関連
	//今押された
	static bool IsMousePush(int Mouse_code);
	//押し続ける
	static bool IsMouseKeep(int Mouse_code);
	//離したとき
	static bool IsMouseRelease(int Mouse_code);

	//マウスの状態を得る
	static void GetHitMouseStateAll();
};


