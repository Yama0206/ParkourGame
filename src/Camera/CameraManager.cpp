#include "CameraManager.h"

//��`�֘A
//��{�ƂȂ鎋�_�E�����X�E�A�b�v�x�N�g��
static const VECTOR DEFAULT_EYE_POS = { 0.0f,  10.0f, -20.0f };
static const VECTOR DEFAULT_FORCUS_POS = { 0.0f, 0.0f, 0.0f };
static const VECTOR DEFAULT_UP_VEC = { 0.0f, 1.0f, 0.0f };

static const float ROTATE_DEBUG_SPEED = 0.1f;						//�f�o�b�O�J�����̉�]���x
static const float CAMERA_MOVE_SPEED = 1.0f;						//�f�o�b�O�J�����̈ړ����x

//�R���X�g���N�^
CCameraManager::CCameraManager()
{
	//�ЂƂ܂������̓Q�[���J������
	m_eCurrentCameraID = CAMERA_ID_PLAY;
	m_vPlayerRotateY = 0.0f;
}

//�f�X�g���N�^
CCameraManager::~CCameraManager(){}

//������
void CCameraManager::Init()
{
	m_cPlayCam.Init(DEFAULT_EYE_POS, DEFAULT_FORCUS_POS, DEFAULT_UP_VEC);		//�v���C���[
	m_cDebugCam.Init(DEFAULT_EYE_POS);											//�f�o�b�O
}

//������
void CCameraManager::Init(VECTOR vPos, VECTOR vForcus, VECTOR vUp)
{
	m_cPlayCam.Init(vPos, vForcus, vUp);
	m_cDebugCam.Init(vPos);
}

//���t���[���Ăԏ���
void CCameraManager::Step(VECTOR vForcus, VECTOR vSpd){
	//�J�����̃^�C�v�ɍ��킹�āA�X�V������ύX����
	switch (m_eCurrentCameraID)
	{
	case CAMERA_ID_PLAY:
		m_cPlayCam.Step(vForcus, vSpd);
		m_cPlayCam.UpDate();
		break;
	case CAMERA_ID_DEBUG:
		m_cDebugCam.Step();
		m_cDebugCam.Update();
		break;
	}
}


// �`��
void CCameraManager::Draw() {
	switch (m_eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		m_cDebugCam.Draw();
	default:
		break;
	}
}

//�J�����̃j�A�E�t�@�[�̐ݒ�
void CCameraManager::SetNearFar(float fNear, float fFar)
{
	SetCameraNearFar(fNear, fFar);
}

// �J�����^�C�v�ύX
void CCameraManager::ChangeCamera(tagCAMERA_ID ID) {
	// ID�ύX
	m_eCurrentCameraID = ID;

	// �ύX��ɃJ������������
	switch (m_eCurrentCameraID)
	{
	case CCameraManager::CAMERA_ID_DEBUG:
		// �f�o�b�O�J����������
		m_cDebugCam.Init(m_cPlayCam.GetPosVEC(), m_vPlayerRotateY);
	default:
		break;
	}

	return;
}

//�v���C���[�̊p�x��ۑ�
void CCameraManager::SetPlayerRot(float vRot){
	m_vPlayerRotateY = vRot;
}

//�I������
void CCameraManager::Fin()
{
}
