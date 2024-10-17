#include "Input.h"


//���݂̃t���[���̃L�[���
char CInput::currentKeyBuf[KEY_BUF_LEN] = { 0 };
//�O�t���[���̃L�[���
char CInput::preKeyBuf[KEY_BUF_LEN] = { 0 };

//���݂̃t���[���̃}�E�X���
int CInput::currentMouseBuf[MOUSE_BUF_LEN] = { 0 };
//�O�t���[���̃}�E�X���
int CInput::preMouseBuf[MOUSE_BUF_LEN] = { 0 };

int CInput::JoypadNum = 0;

//���͐��䏉����
void CInput::InitInput()
{
	//�L�[
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}

	//�}�E�X
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

	//�O�̃t���[���̃}�E�X���ϐ��ɋL�^���Ă���
	for (int index = 0; index < MOUSE_BUF_LEN; index++)
	{
		preMouseBuf[index] = currentMouseBuf[index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf);
	//���݂̃}�E�X�����擾
	GetHitMouseStateAll();
}


//�L�[
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
	//�O�U��ŉ�����Ă���@���@���t����������Ă���
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

bool CInput::IsKeyRelease(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
	{
		return true;
	}
	return false;
}

//������Ă���
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

//void CInput::GetHitPadStateAll()
//{
//	memset(currentPadBuf, 0, sizeof(currentPadBuf));
//
//	//���L�[
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0){
//		//������Ă���
//		currentPadBuf[INPUT_DOWN] = 1;
//	}
//	//���L�[
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_LEFT] = 1;
//	}
//	//�E�L�[
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_RIGHT] = 1;
//	}
//	//��L�[
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_UP] = 1;
//	}
//	//�@1�{�^���`�F�b�N�}�X�N(Z�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_1] = 1;
//	}
//	//�@2�{�^���`�F�b�N�}�X�N(X�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_2] = 1;
//	}
//	//�@3�{�^���`�F�b�N�}�X�N(C�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_3] = 1;
//	}
//	//�@4�{�^���`�F�b�N�}�X�N(A�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_4] = 1;
//	}
//	//�@5�{�^���`�F�b�N�}�X�N(S�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_5] = 1;
//	}
//	//�@6�{�^���`�F�b�N�}�X�N(D�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_6] = 1;
//	}
//	//�@7�{�^���`�F�b�N�}�X�N(Q�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_7] = 1;
//	}
//	//�@8�{�^���`�F�b�N�}�X�N(W�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_8] = 1;
//	}
//	//�@9�{�^���`�F�b�N�}�X�N(ESC�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_9) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_9] = 1;
//	}
//	//�@10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)
//	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_10) != 0) {
//		//������Ă���
//		currentPadBuf[INPUT_10] = 1;
//	}

