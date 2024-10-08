#include "PlayCamera.h"

//��`�֘A
const float VIEWPOINT_SPEED = 0.05f;								//���_�ړ����̑���

//�R���X�g���N�^
CPlayerCamera::CPlayerCamera()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vForcus, 0.0f, sizeof(VECTOR));
	memset(&m_vUp, 0.0f, sizeof(VECTOR));
	memset(&m_vRot, 0.0f, sizeof(VECTOR));
}

CPlayerCamera::~CPlayerCamera() {}

//������
void CPlayerCamera::Init()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));
	memset(&m_vForcus, 0.0f, sizeof(VECTOR));
	memset(&m_vUp, 0.0f, sizeof(VECTOR));
	memset(&m_vRot, 0.0f, sizeof(VECTOR));
	
	m_MousePosX = 0;
	m_MousePosY = 0;
}

void CPlayerCamera::Init(VECTOR vCameraPos, VECTOR vForcusPos, VECTOR vUP)
{
	m_vPos = vCameraPos;
	m_vForcus = vForcusPos;
	m_vUp = vUP;
}

//�J�����̖���Ăԏ���
void CPlayerCamera::Step(VECTOR vForcus, VECTOR vSpd)
{
	//�J�����̎��_�ړ�����
	ViewControl();

	//�����_�̐ݒ�
	m_vForcus = vForcus;

	//�J�����p�̍s��
	MATRIX MoveMatrix;		//���s�ړ��s��
	MATRIX PosMatrix;		//���̈ʒu�ɖ߂��s��
	MATRIX RevMatrix;		//���_�Ɉړ�����s��
	MATRIX Matrix;			//�s��̍����������l�������s��
	MATRIX CameraPosMat;	//�J�����̍��W�s��

	//�J�����̍��W�����߂�
	VECTOR vCameraPos = VAdd(vForcus, VGet(0.0f, CAMERA_OFFSET_Y, -CAMERA_LENGTH));

	MoveMatrix.m[3][3] = 1.0f;
	PosMatrix.m[3][3] = 1.0f;
	RevMatrix.m[3][3] = 1.0f;
	Matrix.m[3][3] = 1.0f;

	//�s��ɒl����
	MoveMatrix = MGetTranslate(vSpd);									//�ړ��s��
	PosMatrix = MGetTranslate(vForcus);									//���W�̍s��
	RevMatrix = MGetTranslate(VScale(vForcus, -1));						//���W�̔��΍s��

	//Y����]�s��̍쐬
	//�����̓��W�A���l
	MATRIX YRot = MGetRotY(m_vRot.y);		//Y����]
	MATRIX XRot = MGetRotX(m_vRot.x);		//X����]

	//�s��̍���
	// ���삳���������ԂŊ|���Z���Ă���
	//�@�ړ��s��~�AY����]
	Matrix = MMult(RevMatrix, XRot);
	Matrix = MMult(Matrix, YRot);
	Matrix = MMult(Matrix, PosMatrix);

	//�s��̍��W�ϊ�
	m_vPos = VTransform(vCameraPos, Matrix);
}

//���_����
void CPlayerCamera::ViewControl()
{
	//1F�O�̉�]�l�����Ă���
	m_vRot = m_vOldRot;

	//X�����ɂǂ��܂ŉ�]�����邩���߂�
	//�p�x�����W�A���ɕϊ�
	float MaxRotX = TransAngleToRadian(73.0f);


	//�L�����N�^�[�̉�]
	if (CInput::IsKeyKeep(KEY_INPUT_RIGHT))
	{
		m_vRot.y += VIEWPOINT_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_LEFT))
	{
		m_vRot.y -= VIEWPOINT_SPEED;
	}
	if (CInput::IsKeyKeep(KEY_INPUT_UP) && fabs(m_vRot.x) < MaxRotX)
	{
		m_vRot.x += -VIEWPOINT_SPEED;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_DOWN) && fabs(m_vRot.x) < MaxRotX)
	{
		m_vRot.x += VIEWPOINT_SPEED;
	}

	if (fabs(m_vRot.x) >= MaxRotX)
	{
		m_vRot = m_vOldRot;
	}

}

//�X�V�����f�[�^�𔽉f
void CPlayerCamera::UpDate()
{
	//1F�O�̉�]�l���X�V
	m_vOldRot = m_vRot;

	//�J�������X�V
	SetCameraPositionAndTargetAndUpVec(m_vPos, m_vForcus, m_vUp);
}