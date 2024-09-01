#pragma once
#include "DxLib.h"

#define KEY_BUF_LEN		(256)
#define MOUSE_BUF_LEN	(5)

static class CInput {
private:
	//���݂̃t���[���̃L�[���
	static char currentKeyBuf[KEY_BUF_LEN];
	//�O�t���[���̃L�[���
	static char preKeyBuf[KEY_BUF_LEN];

	//���݂̃t���[����Pad���
	static char currentPadBuf[KEY_BUF_LEN];
	//�O�t���[����Pad���
	static char prePadBuf[KEY_BUF_LEN];

	//���݂̃t���[���̃}�E�X���
	static int currentMouseBuf[MOUSE_BUF_LEN];
	//�O�t���[���̃}�E�X���
	static int preMouseBuf[MOUSE_BUF_LEN];
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


