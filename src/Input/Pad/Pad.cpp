#include "Pad.h"

//現在のフレームのPad情報
char CPad::currentPadBuf[PAD_BUF_LEN] = { 0 };
//前フレームのPad情報
char CPad::prePadBuf[PAD_BUF_LEN] = { 0 };

void CPad::Init()
{
	//パッド
	for (int index = 0; index < PAD_BUF_LEN; index++)
	{
		currentPadBuf[index] = '\0';
		prePadBuf[index] = '\0';
	} 
}

void CPad::Step()
{
	//前のフレームのキー情報変数に記録しておく
	for (int index = 0; index < PAD_BUF_LEN; index++)
	{
		prePadBuf[index] = currentPadBuf[index];
	}

	GetHitPadStateAll(currentPadBuf);
}

//パッド関連
bool CPad::IsPadPush(int key_code)
{
 
	//前振れで押されてない　かつ　現フレで押されている
	if (prePadBuf[key_code] == 0 && currentPadBuf[key_code] == 1)
		return true;

	//押されてないのでfalse
	return false;
}

bool CPad::IsPadKeep(int key_code)
{
	//前振れで押されている　かつ　現フレも押されている
	if (prePadBuf[key_code] == 1 && currentPadBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

bool CPad::IsPadRelease(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (prePadBuf[key_code] == 1 && currentPadBuf[key_code] == 0)
	{
		return true;
	}
	return false;
}

//押されている
bool CPad::IsPadDown(int key_code)
{
	//現フレで押されている（前振れの状態は関係なし）
	if (currentPadBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

int CPad::GetHitPadStateAll(char* PadBuf)
{
	//下キー
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
		//押されている
		PadBuf[INPUT_DOWN] = 1;
		return 1;
	}
	else 
	{
		//押されていない
		PadBuf[INPUT_DOWN] = 1;
		return -1;
	}
	//左キー
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) {
		//押されている
		PadBuf[INPUT_LEFT] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_LEFT] = 1;
		return -1;
	}
	//右キー
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) {
		//押されている
		PadBuf[INPUT_RIGHT] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_RIGHT] = 1;
		return -1;
	}
	//上キー
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
		//押されている
		PadBuf[INPUT_UP] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_UP] = 1;
		return -1;
	}
	//　A(×)ボタンチェックマスク(Zキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
		//押されている
		PadBuf[PAD_INPUT_1] = '1';
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[PAD_INPUT_1] = 1;
		return -1;
	}
	//　B(〇)ボタンチェックマスク(Xキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
		//押されている
		PadBuf[PAD_INPUT_2] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[PAD_INPUT_2] = 1;
		return -1;
	}
	//　X(□)ボタンチェックマスク(Cキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) {
		//押されている
		PadBuf[INPUT_X] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_X] = 1;
		return -1;
	}
	//　Y(△)ボタンチェックマスク(Aキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0) {
		//押されている
		PadBuf[INPUT_Y] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_Y] = 1;
		return -1;
	}
	//　5ボタンチェックマスク(Sキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
		//押されている
		PadBuf[INPUT_5] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_5] = 1;
		return -1;
	}
	//　6ボタンチェックマスク(Dキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0) {
		//押されている
		PadBuf[INPUT_6] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_6] = 1;
		return -1;
	}
	//　7ボタンチェックマスク(Qキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) != 0) {
		//押されている
		PadBuf[INPUT_7] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_7] = 1;
		return -1;
	}
	//　8ボタンチェックマスク(Wキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0) {
		//押されている
		PadBuf[INPUT_8] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_8] = 1;
		return -1;
	}
	//　9ボタンチェックマスク(ESCキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_9) != 0) {
		//押されている
		PadBuf[INPUT_9] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_9] = 0;
		return -1;
	}
	//　10ボタンチェックマスク(スペースキー)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_10) != 0) {
		//押されている
		PadBuf[INPUT_10] = 1;
		return 1;
	}
	else
	{
		//押されていない
		PadBuf[INPUT_10] = 0;
		return -1;
	}
}

