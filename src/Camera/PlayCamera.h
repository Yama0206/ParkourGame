#pragma once
#include "DxLib.h"
#include "math.h"
#include "../Input/Input.h"
#include "../Math/Math.h"
#include "../Debug/DebugManager.h"

const float CAMERA_LENGTH = 50.0f;								//�J�����̋���
const float CAMERA_OFFSET_Y = 50.0f;							//�J�����̎��_�̍���
const float FORCUS_OFFSET_Y = 10.0f;							//�J�����̒����_�̍���
static const VECTOR CAMERA_SIZE = VGet(5.0f, 5.0f, 5.0f);		//�J�����̃T�C�Y

class CPlayerCamera
{
private:
	VECTOR m_vPos;					//���_
	VECTOR m_vForcus;				//�����_
	VECTOR m_vRot;					//��]�l
	VECTOR m_vOldRot;				//1F�O�̉�]�l
	VECTOR m_vUp;					//�����

	DINPUT_JOYSTATE m_JoyState;		//�p�b�h�̏��

	int* m_MousePosX, * m_MousePosY;	//�}�E�X�̍��W

public:
	//�R���X�g���N�^
	CPlayerCamera();
	~CPlayerCamera();

	//������
	void Init();
	void Init(VECTOR vCameraPos, VECTOR vForcusPos, VECTOR vUP);

	//�J�������W�擾
	VECTOR GetPosVEC()		 { return m_vPos; }				//���_
	VECTOR GetForcusPosVEC() { return m_vForcus; }			//�����_
	VECTOR GetUpVEC()		 { return m_vUp; }				//�����
	VECTOR GetRot()			 { return m_vRot; }				//��]�l

	//�J�����̖���Ăԏ���
	//��1����
	void Step(VECTOR vForcus, VECTOR vSpd);

	//���_����
	void ViewControl();

	//�J�������̍X�V
	void UpDate();
};
