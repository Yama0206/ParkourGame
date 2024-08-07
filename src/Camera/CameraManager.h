#pragma once
#include "PlayCamera.h"
#include "DxLib.h"
#include "../Camera/DebugCamera.h"

class CCameraManager
{
public:
	//�J�����̃^�C�v
	enum tagCAMERA_ID
	{
		CAMERA_ID_PLAY,				//�Q�[�����̃J����
		CAMERA_ID_DEBUG,			//�f�o�b�O�p�̃J����(���㐧��)

		CAMERA_ID_NUM
	};

private:
	CPlayerCamera m_cPlayCam;					//�v���C���[�J����
	CDebugCamera m_cDebugCam;					//�f�o�b�O�p�J����
	tagCAMERA_ID m_eCurrentCameraID;			//���݂̃J����

	float		 m_vPlayerRotateY;				// �v���C���[�̊p�x

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCameraManager();
	~CCameraManager();

	//������
	// @vPos		:	���_
	// @vForcus		:	�����_
	// @vUp			:	�����
	void Init();
	void Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp);

	//��1����, �J�����̃j�A		//��2����, �J�����̃t�@�[	
	void SetNearFar(float fNear, float fFar);

	//�X�V����
	void Step(VECTOR vForcus, VECTOR vSpd);

	// �`��
	void Draw();

	//�J�����^�C�v�ύX
	void ChangeCamera(tagCAMERA_ID ID);

	//���݂̃J�����^�C�v���擾
	tagCAMERA_ID GetCameraID() { return m_eCurrentCameraID; }

	//�v���C���[�̊p�x��ۑ�
	void SetPlayerRot(float vRot);
	VECTOR GetPlayCamRot() { return m_cPlayCam.GetRot(); }

	//�I������
	void Fin();
};




