#pragma once
#include "DxLib.h"

//定義
#define PAD_BUF_LEN		(256)

enum JoyPadKey
{
	INPUT_DOWN = 0,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_A,
	INPUT_B,
	INPUT_X,
	INPUT_Y,
	INPUT_L,
	INPUT_R,
	INPUT_7,
	INPUT_8,
	INPUT_L3,
	INPUT_R3
};

enum DUALSHOCK4_Key
{
	INPUT_DOWN = 0,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_□,
	INPUT_×,
	INPUT_〇,
	INPUT_△,
	INPUT_L2,
	INPUT_R2,
	INPUT_9,
	INPUT_10,
};

static class CPad
{
private:
	//現在のフレームのPad情報
	static char currentPadBuf[PAD_BUF_LEN];
	//前フレームのPad情報
	static char prePadBuf[PAD_BUF_LEN];

	//パッドの接続数
	static int m_PadAllNum;

public:
	static void Init();

	static void Step();

	//Pad関連
//今押された
	static bool IsPadPush(int key_code);
	//押し続ける
	static bool IsPadKeep(int key_code);
	//離したとき
	static bool IsPadRelease(int key_code);
	//押されたかどうか
	static bool IsPadDown(int key_code);

	static void GetHitPadStateAll(char* PadBuf);

};
