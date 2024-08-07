#include "DebugCamera.h"
#include "../Input/Input.h"

// �J�����̋���
#define CAMERA_LENGHT 30.0f

// ���_�̍���
#define CAMERA_OFFSET_Y 10.0f

// �����_�̍���
#define FORCUS_OFFSET_Y 10.0f

// �J�����̈ړ����x
#define CAMERA_MOVE_SPEED 1.0f

// �J�����̉�]���x
#define CAMERA_ROTATE_SPEED 0.02f

// �R���X�g���N�^
CDebugCamera::CDebugCamera() {
	memset(&m_vCameraPos, 0, sizeof(VECTOR));
	memset(&m_vCameraRot, 0, sizeof(VECTOR));
}

// �f�X�g���N�^
CDebugCamera::~CDebugCamera() {}

// ������
void CDebugCamera::Init() {
	// �O�̂��ߏ����l��ݒ�
	m_vCameraPos = VGet(0.0f, 0.0f, 1.0f);
	m_vCameraRot = VGet(0.0f, 0.0f, 1.0f);
}

// ������
void CDebugCamera::Init(VECTOR vPos, float fRot) {
	m_vCameraPos = vPos;
	m_vCameraRot.y = fRot + DX_PI_F;
}

// ���t���[�����s���鏈��
void CDebugCamera::Step() {
	// �J�����̈ړ��̑���
	VECTOR fSpd = { 0.0f, 0.0f, 0.0f };
	if (CheckHitKey(KEY_INPUT_W)) {
		fSpd.z = CAMERA_MOVE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		fSpd.z = -CAMERA_MOVE_SPEED;
	}
	float fRot = 0.0f;
	if (CheckHitKey(KEY_INPUT_A)) {
		fSpd.x = -CAMERA_MOVE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		fSpd.x = CAMERA_MOVE_SPEED;
	}
	if (CInput::IsKeyKeep(KEY_INPUT_E))
	{
		fSpd.y = CAMERA_MOVE_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_Q))
	{
		fSpd.y = -CAMERA_MOVE_SPEED;
	}

	// �J�����̌����̑���
	if (CheckHitKey(KEY_INPUT_UP)) {
		m_vCameraRot.x -= CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		m_vCameraRot.x += CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		m_vCameraRot.y -= CAMERA_ROTATE_SPEED;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		m_vCameraRot.y += CAMERA_ROTATE_SPEED;
	}

	MATRIX matrix1, matrix2, matrix3, matrix4;
	VECTOR vPos = VScale(m_vCameraPos, -1);

	matrix1.m[3][3] = 1.0f;
	matrix2.m[3][3] = 1.0f;
	matrix3.m[3][3] = 1.0f;
	matrix4.m[3][3] = 1.0f;

	matrix1 = MGetTranslate(fSpd);
	matrix2 = MGetTranslate(vPos);
	matrix3 = MGetTranslate(m_vCameraPos);

	//Y����]�s��̍쐬
	//�����̓��W�A���l
	MATRIX YRot = MGetRotY(m_vCameraRot.y);
	MATRIX XRot = MGetRotX(m_vCameraRot.x);

	//�s��̍���
	// ���삳���������ԂŊ|���Z���Ă���
	//�@�ړ��s��~�AY����]
	matrix4 = MMult(matrix2, matrix1);
	matrix4 = MMult(matrix4, XRot);
	matrix4 = MMult(matrix4, YRot);
	matrix4 = MMult(matrix4, matrix3);


	//�s��̍��W�ϊ�
	m_vCameraPos = VTransform(m_vCameraPos, matrix4);
}

// �`��
void CDebugCamera::Draw() {
	DrawString(0, 0, "�f�o�b�O�J�������[�h", GetColor(0, 255, 0));
}

// �X�V�����f�[�^�𔽉f
void CDebugCamera::Update() {
	SetCameraPositionAndAngle(m_vCameraPos, m_vCameraRot.x, m_vCameraRot.y, m_vCameraRot.z);
}