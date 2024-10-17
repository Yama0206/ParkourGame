//2309426_�ΎRᩑ� �A�E��i


#include "DxLib.h"				//DX���C�u�����̃C���N���[�h
#include "Input/Input.h"	
#include "Input/Pad/Pad.h"	
#include "Fps/Fps.h"
#include "Scene/SceneManager.h"
#include "CheckPoint/Manager/CheckPointManager.h"
#include "Debug/DebugManager.h"

// define
#define	SCREEN_SIZE_X	1280	// X�����̉�ʃT�C�Y���w��
#define	SCREEN_SIZE_Y	720	// Y�����̉�ʃT�C�Y���w��

const char BULLET_PATH[] = { "data/shot/plshot.x" };

// Win32�A�v���P�[�V������ WinMain�֐� ����n�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// ��ʃT�C�Y��ύX
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//�`�悷��X�N���[����ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	//Z�o�b�t�@���g�p����ꍇTRUE
	SetUseZBuffer3D(TRUE);
	
	//-----------------------------------------
	//��ԍŏ��ɂP�񂾂���鏈���������ɏ���
	
	//�V�[��
	SceneManager cSceneManager;

	//���͊֘A������
	CInput::InitInput();
	CPad::Init();

	 int iHndl = MV1LoadModel(BULLET_PATH);
	//-----------------------------------------

	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1);

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			//�G�X�P�[�v�L�[�������ꂽ��I��
			break;
		}

		//�t���[�����[�g����
		FpsControll_Update();

		//��ʂɕ\�����ꂽ���̂�������
		ClearDrawScreen();

		//-----------------------------------------
		//��������Q�[���̖{�̂��������ƂɂȂ�
		//-----------------------------------------
		
		//���͊֘A
		CInput::StepInput();
		CPad::Step();


		cSceneManager.Loop();
		cSceneManager.Draw();


		//Fps����------------------------------
		InitFPS();							//FPS�̏�����	
		CalcFPS();							//FPS�̌v�Z
		StepFPS();							//FPS�̒ʏ폈��		
		DrawFPS();							//FPS�̕\��		
		SetNowTimeFps();					//���݂̎��Ԃ�ݒ�		
		IsExecuteFPS();						//�O��̎��s������s�\�t���[�����`�F�b�N	
		FpsControll_Wait();					//�ҋ@
		//-------------------------------------

		//-----------------------------------------
		//���[�v�̏I����
		//�t���b�v�֐�
		ScreenFlip();

	}

	//-----------------------------------------
	//�Ō�ɂP�񂾂���鏈���������ɏ���
	//�`�F�b�N�|�C���g�N���X���폜
	CCheckPointManager::DeleteInstance();
	CDebugManager::DeleteInstance();
	//-----------------------------------------
	//DX���C�u�����̌㏈��
	DxLib_End();

	return 0;
}

