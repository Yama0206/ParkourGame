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
