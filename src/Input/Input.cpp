#include "Input.h"


//���݂̃t���[���̃L�[���
char CInput::currentKeyBuf[KEY_BUF_LEN] = { 0 };
//�O�t���[���̃L�[���
char CInput::preKeyBuf[KEY_BUF_LEN] = { 0 };
//���݂̃t���[���̃}�E�X���
int CInput::currentMouseBuf[MOUSE_BUF_LEN] = { 0 };
//�O�t���[���̃}�E�X���
int CInput::preMouseBuf[MOUSE_BUF_LEN] = { 0 };


//���͐��䏉����
void CInput::InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		currentMouseBuf[index] = 0;
		preMouseBuf[index] = 0;
	}
}

//���͐���̃X�e�b�v
//�ق��̃X�e�b�v��葁���Ă�
void CInput::StepInput()
{
	//�O�̃t���[���̃L�[���ϐ��ɋL�^���Ă���
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}
	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf);
	//���݂̃}�E�X�����擾
	GetHitMouseStateAll();
}

bool CInput::IsKeyPush(int key_code)
{
	//�O�U��ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//������ĂȂ��̂�false
	return false;
}

bool CInput::IsKeyKeep(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

bool CInput::IsKeyRelease(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}
	return false;
}

bool CInput::IsKeyDown(int key_code)
{
	//���t���ŉ�����Ă���i�O�U��̏�Ԃ͊֌W�Ȃ��j
	if (currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}


//�}�E�X�֘A
bool CInput::IsMousePush(int Mouse_code)
{
	//�O�U��ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (preMouseBuf[Mouse_code] == 0 && currentMouseBuf[Mouse_code] != 0) {
		return true;
	}

	//������ĂȂ��̂�false
	return false;
}


bool CInput::IsMouseKeep(int Mouse_code)
{
	if (preMouseBuf[Mouse_code] == 1 && currentMouseBuf[Mouse_code] == 1)
	{
		return true;
	}

	return false;
}

bool CInput::IsMouseRelease(int Mouse_code)
{
	if (preMouseBuf[Mouse_code] == 1 && currentMouseBuf[Mouse_code] == 0)
	{
		return true;
	}
	return false;
}

//�}�E�X�̓��͂��ꂽ��Ԃ𓾂�
void CInput::GetHitMouseStateAll()
{
	memset(currentMouseBuf, 0, sizeof(currentMouseBuf));

	if (GetMouseInput() && MOUSE_INPUT_LEFT != 0) {
		currentMouseBuf[0] = MOUSE_INPUT_LEFT;
	}
	else if(GetMouseInput() && MOUSE_INPUT_RIGHT){
		currentMouseBuf[1] = MOUSE_INPUT_RIGHT;
	}
	else if (GetMouseInput() && MOUSE_INPUT_MIDDLE) {
		currentMouseBuf[2] = MOUSE_INPUT_MIDDLE;
	}
}
