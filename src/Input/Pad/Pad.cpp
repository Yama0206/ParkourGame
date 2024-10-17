#include "Pad.h"

//���݂̃t���[����Pad���
char CPad::currentPadBuf[PAD_BUF_LEN] = { 0 };
//�O�t���[����Pad���
char CPad::prePadBuf[PAD_BUF_LEN] = { 0 };

void CPad::Init()
{
	//�p�b�h
	for (int index = 0; index < PAD_BUF_LEN; index++)
	{
		currentPadBuf[index] = '\0';
		prePadBuf[index] = '\0';
	} 
}

void CPad::Step()
{
	//�O�̃t���[���̃L�[���ϐ��ɋL�^���Ă���
	for (int index = 0; index < PAD_BUF_LEN; index++)
	{
		prePadBuf[index] = currentPadBuf[index];
	}

	GetHitPadStateAll(currentPadBuf);
}

//�p�b�h�֘A
bool CPad::IsPadPush(int key_code)
{
 
	//�O�U��ŉ�����ĂȂ��@���@���t���ŉ�����Ă���
	if (prePadBuf[key_code] == 0 && currentPadBuf[key_code] == 1)
		return true;

	//������ĂȂ��̂�false
	return false;
}

bool CPad::IsPadKeep(int key_code)
{
	//�O�U��ŉ�����Ă���@���@���t����������Ă���
	if (prePadBuf[key_code] == 1 && currentPadBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

bool CPad::IsPadRelease(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (prePadBuf[key_code] == 1 && currentPadBuf[key_code] == 0)
	{
		return true;
	}
	return false;
}

//������Ă���
bool CPad::IsPadDown(int key_code)
{
	//���t���ŉ�����Ă���i�O�U��̏�Ԃ͊֌W�Ȃ��j
	if (currentPadBuf[key_code] == 1)
	{
		return true;
	}

	return false;
}

int CPad::GetHitPadStateAll(char* PadBuf)
{
	//���L�[
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0) {
		//������Ă���
		PadBuf[INPUT_DOWN] = 1;
		return 1;
	}
	else 
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_DOWN] = 1;
		return -1;
	}
	//���L�[
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) {
		//������Ă���
		PadBuf[INPUT_LEFT] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_LEFT] = 1;
		return -1;
	}
	//�E�L�[
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) {
		//������Ă���
		PadBuf[INPUT_RIGHT] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_RIGHT] = 1;
		return -1;
	}
	//��L�[
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0) {
		//������Ă���
		PadBuf[INPUT_UP] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_UP] = 1;
		return -1;
	}
	//�@A(�~)�{�^���`�F�b�N�}�X�N(Z�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
		//������Ă���
		PadBuf[PAD_INPUT_1] = '1';
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[PAD_INPUT_1] = 1;
		return -1;
	}
	//�@B(�Z)�{�^���`�F�b�N�}�X�N(X�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
		//������Ă���
		PadBuf[PAD_INPUT_2] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[PAD_INPUT_2] = 1;
		return -1;
	}
	//�@X(��)�{�^���`�F�b�N�}�X�N(C�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) {
		//������Ă���
		PadBuf[INPUT_X] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_X] = 1;
		return -1;
	}
	//�@Y(��)�{�^���`�F�b�N�}�X�N(A�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0) {
		//������Ă���
		PadBuf[INPUT_Y] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_Y] = 1;
		return -1;
	}
	//�@5�{�^���`�F�b�N�}�X�N(S�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
		//������Ă���
		PadBuf[INPUT_5] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_5] = 1;
		return -1;
	}
	//�@6�{�^���`�F�b�N�}�X�N(D�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0) {
		//������Ă���
		PadBuf[INPUT_6] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_6] = 1;
		return -1;
	}
	//�@7�{�^���`�F�b�N�}�X�N(Q�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7) != 0) {
		//������Ă���
		PadBuf[INPUT_7] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_7] = 1;
		return -1;
	}
	//�@8�{�^���`�F�b�N�}�X�N(W�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0) {
		//������Ă���
		PadBuf[INPUT_8] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_8] = 1;
		return -1;
	}
	//�@9�{�^���`�F�b�N�}�X�N(ESC�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_9) != 0) {
		//������Ă���
		PadBuf[INPUT_9] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_9] = 0;
		return -1;
	}
	//�@10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_10) != 0) {
		//������Ă���
		PadBuf[INPUT_10] = 1;
		return 1;
	}
	else
	{
		//������Ă��Ȃ�
		PadBuf[INPUT_10] = 0;
		return -1;
	}
}

