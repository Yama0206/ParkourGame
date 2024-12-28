#pragma once
#include "DxLib.h"

//��`
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
	DUALSHOCK4_INPUT_DOWN = 0,
	DUALSHOCK4_INPUT_LEFT,
	DUALSHOCK4_INPUT_RIGHT,
	DUALSHOCK4_INPUT_UP,
	DUALSHOCK4_INPUT_RECT = 4,
	DUALSHOCK4_INPUT_CROSS,
	DUALSHOCK4_INPUT_CIRCLE,
	DUALSHOCK4_INPUT_TRIANGLE,
	DUALSHOCK4_INPUT_L2,
	DUALSHOCK4_INPUT_R2,
	DUALSHOCK4_INPUT_9,
	DUALSHOCK4_INPUT_10,
};

static class CPad
{
private:
	//���݂̃t���[����Pad���
	static char currentPadBuf[PAD_BUF_LEN];
	//�O�t���[����Pad���
	static char prePadBuf[PAD_BUF_LEN];

	//�p�b�h�̐ڑ���
	static int m_PadAllNum;

public:
	static void Init();

	static void Step();

	//Pad�֘A
//�������ꂽ
	static bool IsPadPush(int key_code);
	//����������
	static bool IsPadKeep(int key_code);
	//�������Ƃ�
	static bool IsPadRelease(int key_code);
	//�����ꂽ���ǂ���
	static bool IsPadDown(int key_code);

	static void GetHitPadStateAll(char* PadBuf);

};
