#pragma once

#define DEF_FPSCONTROLL_H


//�ݒ�t���[�����[�g
#define FRAME_RATE	(60)

//1�t���[���̎��ԁi�~���b�j
#define FRAME_TIME	(1000 / FRAME_RATE)

//�t���[�����[�g���
struct FrameRateInfo
{
	int currentTime;	//���݂̎���
	int lastFreamTime;	//�O��̃t���[�����s���̎���
	int count;			//�t���[���J�E���g�p
	int calcFpsTime;	//FPS���v�Z��������
	float fps;			//�v������FPS�i�\���p�j	
};


// FPS����������
void InitFPS();

//FPS�v�Z
void CalcFPS();

//FPS�\���i�f�o�b�O�p�j
void DrawFPS();

//���݂̎��Ԃ�ݒ�
void SetNowTimeFps();

// �O��̎��s������s�\�t���[�����`�F�b�N
bool IsExecuteFPS();

// FPS�̒ʏ폈��
void StepFPS();


//�t���[���[�g�̐���
void FpsControll_Initialize();

//FPS����
bool FpsControll_Update();

//FPS�\��
void FpsControll_Draw();

void FpsControll_Wait();