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
	INPUT_DOWN = 0,
	INPUT_LEFT,
	INPUT_RIGHT,
	INPUT_UP,
	INPUT_��,
	INPUT_�~,
	INPUT_�Z,
	INPUT_��,
	INPUT_L2,
	INPUT_R2,
	INPUT_9,
	INPUT_10,
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
