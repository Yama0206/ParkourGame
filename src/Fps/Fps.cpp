#include "DxLib.h"
#include "Fps.h"
#include <math.h>

//�t���[�����[�g����
static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;  //���ς����T���v����
static const int FPS = 60;  //�ݒ肵��FPS


FrameRateInfo frameRateInfo = { 0 };

// FPS����������
void InitFPS()
{
	// ���݂̎��Ԃ��AFPS�̌v�Z�������Ԃɐݒ�
	if (frameRateInfo.calcFpsTime == 0.0f) {
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}
}

// FPS�X�V����
void SetNowTimeFps()
{
	// ���݂̎��Ԃ��擾
	frameRateInfo.currentTime = GetNowCount();
}

// FPS�v�Z
void CalcFPS() {
	// �O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	// �O���FPS���v�Z�������Ԃ���
	// 1�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000) {
		// �t���[���񐔂��~���b�ɍ��킹��
		// �����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		// FPS�����߂�
		// ���z�̐��l��60000/1000��60�ƂȂ�
		frameRateInfo.fps = frameCount / difTime;

		// �t���[�����[�g�J�E���g���N���A
		frameRateInfo.count = 0;

		// FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

// FPS�\���i�f�o�b�O�p�j
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1100, 50, color, "FPS[%.2f]", frameRateInfo.fps);
}

// �O��̎��s������s�\�t���[�����`�F�b�N
bool IsExecuteFPS()
{
	if (frameRateInfo.currentTime - frameRateInfo.lastFreamTime >= FRAME_TIME)
	{
		return true;
	}
	return false;
}

// FPS�̒ʏ폈��
void StepFPS()
{
	// �t���[�����s���̎��Ԃ��X�V
	frameRateInfo.lastFreamTime = frameRateInfo.currentTime;

	// �t���[�������J�E���g
	frameRateInfo.count++;
}


//�t���[�����[�g�̐���


//������
void FpsControll_Initialize() {
	mStartTime = GetNowCount();
	mCount = 0;
	mFps = 0;
}

//FPS����
bool FpsControll_Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void FpsControll_Wait() {
	int tookTime = GetNowCount() - mStartTime;  //������������
	int waitTime = mCount * 1000 / FPS - tookTime;  //�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);  //�ҋ@
	}
}