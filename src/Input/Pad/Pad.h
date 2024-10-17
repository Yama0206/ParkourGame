#pragma once
#include "DxLib.h"

//��`
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

	//static void StepInputPad();

	//Pad�֘A
//�������ꂽ
	static bool IsPadPush(int key_code);
	//����������
	static bool IsPadKeep(int key_code);
	//�������Ƃ�
	static bool IsPadRelease(int key_code);
	//�����ꂽ���ǂ���
	static bool IsPadDown(int key_code);

};
