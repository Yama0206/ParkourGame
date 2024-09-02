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
	//���݂̃t���[���̃L�[���
	static char currentKeyBuf[KEY_BUF_LEN];
	//�O�t���[���̃L�[���
	static char preKeyBuf[KEY_BUF_LEN];

	//���݂̃t���[����Pad���
	static char currentPadBuf[PAD_BUF_LEN];
	//�O�t���[����Pad���
	static char prePadBuf[PAD_BUF_LEN];

	//���݂̃t���[���̃}�E�X���
	static int currentMouseBuf[MOUSE_BUF_LEN];
	//�O�t���[���̃}�E�X���
	static int preMouseBuf[MOUSE_BUF_LEN];

	static int JoypadNum;
public:
	//������͂��ꂽ��
	static const int MOUSE_LEFT = 0;
	static const int MOUSE_RIGHT = 1;
	static const int MOUSE_MIDLE = 2;

	//���͐��䏉����
	static void InitInput();

	//���͐���X�e�b�v
	//�ق���Step��葁���Ă�
	static void StepInput();
	static void StepInputPad();


	//�L�[�{�[�h�֘A
	//�������ꂽ
	static bool IsKeyPush(int key_code);
	//����������
	static bool IsKeyKeep(int key_code);
	//�������Ƃ�
	static bool IsKeyRelease(int key_code);

	static bool IsKeyDown(int key_code);

	//Pad�֘A
	//�������ꂽ
	static bool IsPadPush(int key_code);
	//����������
	static bool IsPadKeep(int key_code);
	//�������Ƃ�
	static bool IsPadRelease(int key_code);
	//�����ꂽ���ǂ���
	static bool IsPadDown(int key_code);

	//�p�b�h�̓��͏�Ԃ𓾂�
	static void GetHitPadStateAll();

	//�}�E�X�֘A
	//�������ꂽ
	static bool IsMousePush(int Mouse_code);
	//����������
	static bool IsMouseKeep(int Mouse_code);
	//�������Ƃ�
	static bool IsMouseRelease(int Mouse_code);

	//�}�E�X�̏�Ԃ𓾂�
	static void GetHitMouseStateAll();
};


