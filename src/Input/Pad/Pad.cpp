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
