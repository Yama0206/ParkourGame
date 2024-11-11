#include "Player.h"

//��`�֘A
static constexpr float VIEWPOINT_SPEED = 0.1f;					//�v���C���[�̉�]���x
static constexpr float MOVE_SPEED = 1.0f;						//�v���C���[�̈ړ����x
static constexpr float ADD_SPEED = 0.2f;						//�v���C���[�̃X�s�[�h�����Z����
static constexpr float SAB_SPEED = 0.1f; 						//�v���C���[�̃X�s�[�h�����Z����
static constexpr float DASH_SPEED = 2.0f;						//�v���C���[�����������̈ړ����x
static constexpr float GRAVITY = 0.2f;							//�v���C���[�̏d��
static constexpr float MAX_GRAVITY = 3.0f;						//�v���C���[�̏d�͂̌��E
static constexpr float MIN_GRAVITY = 0.1f;						//�v���C���[�̏d�͂̍Œ�
static constexpr float YSPEED = 4.0f;							//�v���C���[��Y�����̃X�s�[�h
static constexpr float ROTATE_SPEED = 0.1f;						//��]�X�s�[�h
static constexpr float SCALE = 0.1f;							//�g��k����
	
//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�ЂƂ܂����������Ă���
	m_eState = PLAYER_STATE_NORMAL;				//�v���C���[�̏��
}
//�f�X�g���N�^
CPlayer::~CPlayer()
{
	//�ЂƂ܂����S�����Ȓl�����Ă���
	Delete();
	Fin();
}

//�����l�ݒ�
void CPlayer::InitValue()
{
	//�񋓌^
	m_eState = PLAYER_STATE_NORMAL;				//�v���C���[�̏��
	m_eDir = FRONT;								//�v���C���[�̕���

	//�ϐ�
	memset(&m_ViewRot, 0.0f, sizeof(m_ViewRot));	
	m_vScale = { SCALE , SCALE , SCALE };
	m_PadXBuf = 0;
	m_PadYBuf = 0;
	m_fMoveSpeed = 0.0f;										
	m_fChangeRot = 0.0f;											
	m_fGravity = GRAVITY;

	//�t���O
	memset(&m_IsHit, false, sizeof(bool));						
	memset(&m_IsHitLength, false, sizeof(bool));
	memset(&m_IsKeyHit, false, sizeof(bool));				
	memset(&m_IsJump, false, sizeof(bool));						

	m_vPos.y = 100.0f;
}

//���t���[���Ăԏ���
void CPlayer::Step(CShotManager& cShotManager, CCameraManager& cCameraManager)
{
	if (m_IsAllive) {
		switch (m_sAnimData.m_iID)
		{
		case ANIMID_DEFAULT:
			ExecDefault();
			break;
		case ANIMID_WALK:
			ExecWalk();
			break;
		case ANIMID_RUN:
			ExecRun();
			break;
			case ANIMID_JUMP:
			ExecJump();
			break;
			//case ANIMID_UPDOWN:
			//	ExecUpDown();
			//	break;
			//case ANIMID_SHAKE:
			//	ExecShake();
			//	break;
			//case ANIMID_PIANO:
			//	ExecPiano();
			//	break;
			//case ANIMID_DANCE:
			//	ExecDance();
			//	break;
		}
		//�e�̔��ˊ֐�
		Shot(cShotManager);
		//����֐�
		Control(cCameraManager.GetPlayCamRot());

		//�d�͏���
		Gravity();
	}

}

//�f�[�^�֘A�̔j��
void CPlayer::Delete()
{
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//�I������
void CPlayer::Fin()
{
	//���̓v���C���[�����̂Ƃ���K�{�����͂Ȃ�
	//�m�ۂ��Ă������������������Ȃǂ��L�q����Ƃ悢
}

//�i��ł�������`�F�b�N
void CPlayer::GetMoveDir(bool* _DirArray)
{
	//�E�����̃`�F�b�N
	if (m_vNextPos.x < m_vPos.x) {
		_DirArray[RIGHT] = true;
	}
	//�������`�F�b�N�@
	if (m_vNextPos.x > m_vPos.x) {
		_DirArray[LEFT] = true;
	}
	//�������`�F�b�N
	if (m_vNextPos.y < m_vPos.y) {
		_DirArray[DOWN] = true;
	}
	//������`�F�b�N
	if (m_vNextPos.y > m_vPos.y) {
		_DirArray[UP] = true;
	}
	//�������`�F�b�N
	if (m_vNextPos.z < m_vPos.z) {
		_DirArray[FRONT] = true;
	}
	//��O�����`�F�b�N
	if (m_vNextPos.z > m_vPos.z) {
		_DirArray[BACK] = true;
	}
}

//�v���C���[�̌�����ς���
void CPlayer::ChangeDir(int FreamCnt)
{
	//W�L�[�������Ƃ�
	//�i�s�����ɉ�]������
	if (FreamCnt % 60 == 0 && m_fChangeRot > -180.0f) {
		//1F����30�x��]
		m_fChangeRot -= 30;
	}
	//��]����������
	if (m_fChangeRot > -180)
	{
		//�L�[���������t���O��܂�
		m_IsKeyHit = false;
	}
}

//����֐�
void CPlayer::Control(VECTOR vRot)
{
	//�v���C���[�̃t���[���J�E���g�p�ϐ�
	int FreamCnt = 0;

	//�ړ����Ă��邩�̃`�F�b�N
	m_vNextPos = m_vPos;

	//���X�e�B�b�N�̏����擾
	GetJoypadAnalogInput(&m_PadXBuf, &m_PadYBuf, DX_INPUT_PAD1);

	//Pad
	//��ԕύX
	//StateChange_Pad();
	//��Ԃ��Ƃɖ���s������
	//StateStep(vRot);

	//�L�[�{�[�h����
	Control_KeyBord(vRot);

	//�W�����v����
	Jamp(vRot);


	//���͂����L�[���ƃv���C���[�̊p�x����ړ����x�����߂�
	//�ړ��x�N�g���̌v�Z
	Camera = vRot.y;
	Player = fRot;

	m_vSpd.x = sinf(vRot.y + fRot) * m_fMoveSpeed;
	m_vSpd.z = cosf(vRot.y + fRot) * m_fMoveSpeed;

	//�ړ����x�����݂̍��W�ɉ��Z����
	m_vNextPos.x += m_vSpd.x;
	m_vNextPos.z += m_vSpd.z;
}

//�W�����v����
void CPlayer::Jamp(VECTOR vRot)
{
	//�X�y�[�X�L�[���������Ƃ�
	if (CInput::IsKeyPush(KEY_INPUT_SPACE) && !m_IsJump)
	{
		m_eState = PLAYER_STATE_JUMP;
		//m_IsJump = true;
		m_vSpd.y = YSPEED;
	}

	if (m_eState == PLAYER_STATE_JUMP)
	{
		m_IsJump = true;
		m_vSpd.y = YSPEED;
	}
}

//�d�͏���
void CPlayer::Gravity()
{
	//�v���C���[�̏d�͂̏��
	//�v���C���[�����̂ɓ������Ă���Ƃ��͏d�͂��~�߂�
	
	if (!m_IsHitLength) {
		if (m_vSpd.y > -MAX_GRAVITY) {
			m_vSpd.y -= m_fGravity;
		}
	}

	//�v���C���[��Y���W�Ƀv���C���[��Y�X�s�[�h����
	m_vNextPos.y += m_vSpd.y;
}

void CPlayer::StateChange_Pad()
{
	//�p�b�h�̍��X�e�B�b�N���͂��n�܂�����
	if (m_PadXBuf != 0 || m_PadYBuf != 0)
	{
		//�_�b�V���ȊO�̏ꍇ
		if (m_eState != PLAYER_STATE_DASH && m_eState != PLAYER_STATE_JUMP) {
			//�����Ă���
			m_eState = PLAYER_STATE_WALK;
		}
	}
	//L3�{�^����������Ă��v���C���[�������Ă�����
	if (CPad::IsPadKeep(INPUT_R) && m_eState == PLAYER_STATE_WALK) {
		//��Ԃ��_�b�V���ɕύX
		m_eState = PLAYER_STATE_DASH;
	}
	//���łɃ_�b�V���������ꍇ
	else if (CPad::IsPadRelease(INPUT_R) && m_eState == PLAYER_STATE_DASH) {
		//�����ɖ߂�
		m_eState = PLAYER_STATE_WALK;
	}
	//�W�����v����
	if (CPad::IsPadPush(INPUT_A) && !m_IsJump && (m_eState == PLAYER_STATE_WALK || m_eState == PLAYER_STATE_DASH))
	{
		m_eOldState = m_eState;
		m_eState = PLAYER_STATE_JUMP;
	}
	//�W�����v���I������u��
	else if (m_IsJump && m_eState == PLAYER_STATE_JUMP)
	{
		m_eState = m_eOldState;
	}
	//�������ꍇ
	else if ((m_PadXBuf == 0 && m_PadYBuf == 0) && (m_eState == PLAYER_STATE_DASH || m_eState == PLAYER_STATE_WALK)) {
		//�ҋ@���[�V�����ɕύX
		m_eState = PLAYER_STATE_NORMAL;
	}
	/*else {
		�ҋ@���[�V�����ɕύX
		m_eState = PLAYER_STATE_NORMAL;
	}*/
}

void CPlayer::StateStep(VECTOR vRot)
{
	//���X�e�B�b�N���X���Ă���Ƃ�
	if (m_PadXBuf != 0 || m_PadYBuf != 0) {
		//�X�e�B�b�N�̊p�x�ɍ��킹�ăv���C���[����]
		fRot = atan2f((float)m_PadXBuf * -1, (float)m_PadYBuf);
		//�v���C���[����]
		m_ViewRot.y = vRot.y + fRot;
	}

	//�ҋ@��Ԃ̂Ƃ�
	if (m_eState == PLAYER_STATE_NORMAL) {
		//�����X�s�[�h��0.01�ȏ゠�����ꍇ
		if (fabs(m_fMoveSpeed) > 0.01f) {
			//�������Ƃ��̎~�܂�܂ł̗P�\
			m_fMoveSpeed *= 0.9;
		}
		else {
			//�X�s�[�h��0��
			m_fMoveSpeed = 0.0f;
		}
	}
	//�����Ă���Ƃ��̏���
	else if (m_eState == PLAYER_STATE_WALK) {

		//�ʏ�X�s�[�h�܂ŏ��������炷
		if (m_fMoveSpeed > -MOVE_SPEED) {
			//�������Z
			m_fMoveSpeed -= ADD_SPEED;
		}
		else {
			//�������Z
			m_fMoveSpeed -= ADD_SPEED;
		}
		//�ő�l������
		if (m_fMoveSpeed < -MOVE_SPEED) {
			//�������Z
			m_fMoveSpeed = -MOVE_SPEED;
		}
	}
	//�_�b�V�����̏���
	else if (m_eState == PLAYER_STATE_DASH) {
		//�����������Ă���
		m_fMoveSpeed -= ADD_SPEED;

		//�v���C���[�̃_�b�V���X�s�[�h�̏��
		if (m_fMoveSpeed < -DASH_SPEED) {
			m_fMoveSpeed = -DASH_SPEED;
		}
	}
}

void CPlayer::Control_KeyBord(VECTOR vRot)
{
	//�L�[�{�[�h
	//W�L�[�������ꂽ�Ƃ�
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		//�����Ă���
		m_eState = PLAYER_STATE_WALK;

		//�L�[�������ꂽ�t���OON
		m_IsKeyHit = true;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l������
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = DX_PI_F;
		//���f������]������
		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		//�����Ă���
		m_eState = PLAYER_STATE_WALK;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			//����
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = 0.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		//�����Ă���
		m_eState = PLAYER_STATE_WALK;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l������
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		//��]�l
		fRot = 90.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D))
	{
		//�����Ă���
		m_eState = PLAYER_STATE_WALK;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = -90.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_ViewRot.y = vRot.y + fRot;
	}
	else {
		m_eState = PLAYER_STATE_NORMAL;
		//�����X�s�[�h��0.01�ȏ゠�����ꍇ
		if (fabs(m_fMoveSpeed) > 0.01f) {
			//�������Ƃ��̎~�܂�܂ł̗P�\
			m_fMoveSpeed *= 0.9;
		}
		else {
			m_fMoveSpeed = 0.0f;
		}
	}

}


//�e�̔���
void CPlayer::Shot(CShotManager& cShotManager)
{
	if (CInput::IsKeyPush(KEY_INPUT_Z))
	{
		//�v���C���[�̑̂���o��悤�ɍ��W���グ��
		VECTOR vPos = m_vPos;
		vPos.y += 5.0f;
		//���x�̓v���C���[�Ɠ������@�ňړ����������߂�
		VECTOR vSpd;
		const float SHOT_SPEED = 5.0f;
		vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

void CPlayer::Update()
{
	//1F�O�̃v���C���[�̍��W���X�V����
	m_vPos = m_vNextPos;

	MV1SetRotationXYZ(m_iHndl, m_ViewRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}

void CPlayer::Draw()
{
	if (m_IsAllive) {
		MV1DrawModel(m_iHndl);
	}
}

//�������Ă��Ȃ��Ƃ�
void CPlayer::ExecDefault()
{
	//�ҋ@
	if (m_eState == PLAYER_STATE_NORMAL)
	{
		RequestLoop(ANIMID_DEFAULT, 10.0f);
	}
	//�����Ă����Ԃ̎�
	else if (m_eState == PLAYER_STATE_WALK)
	{
		OutputDebugString("�O");
		RequestLoop(ANIMID_WALK, 1.0f);
	}
	//�����Ă����Ԃ̎�
	else if (m_eState == PLAYER_STATE_DASH)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_Z))
	{
		//Z�L�[���Ԃ�Ԃ炷��
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
}

//�����Ă���Ƃ�
void CPlayer::ExecWalk()
{
	//W�L�[�𗣂����Ƃ�
	if (m_eState == PLAYER_STATE_NORMAL)
	{
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
	//�V�t�g�L�[�������Ă���Ƃ�
	if (m_eState == PLAYER_STATE_DASH)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	if (m_eState == PLAYER_STATE_JUMP)
	{
		Request(ANIMID_JUMP, 1.0f);
	}
}

//�����Ă���Ƃ�
void CPlayer::ExecRun()
{
	//W�L�[��b�����Ƃ�
	if (m_eState == PLAYER_STATE_WALK)
	{
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
	//W�L�[�𗣂����Ƃ�
	if (m_eState == PLAYER_STATE_NORMAL)
	{
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
	//�W�����v�����Ƃ�
	if (m_eState == PLAYER_STATE_JUMP)
	{
		Request(ANIMID_JUMP, 1.0f);
	}
}

void CPlayer::ExecJump()
{
	if (!m_IsJump) {
		//�ʏ킾������
		if (m_eState == PLAYER_STATE_NORMAL) {
			RequestLoop(ANIMID_DEFAULT, 1.0f);
		}
		//�����Ă�����
		if (m_eState == PLAYER_STATE_WALK) {
			RequestLoop(ANIMID_DEFAULT, 1.0f);
		}
		//�����Ă�����
		if (m_eState == PLAYER_STATE_DASH) {
			RequestLoop(ANIMID_RUN, 1.0f);
		}
	}
}

//�T�C�Y�擾
void CPlayer::GetSize(VECTOR& vSize)
{
	 vSize = m_vSize;
}

//�T�C�Y�ݒ�
VECTOR CPlayer::SetSize()
{
	return m_vSize = { PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH };
}

//�v���C���[�̈ړ�����W�ݒ�
void CPlayer::SetNextPosX(float vNextPosX)
{
	m_vNextPos.x = vNextPosX;
}
void CPlayer::SetNextPosY(float vNextPosY)
{
	m_vNextPos.y = vNextPosY;
}
void CPlayer::SetNextPosZ(float vNextPosZ)
{
	m_vNextPos.z = vNextPosZ;
}
//�v���C���[�̍��W�ݒ�
void CPlayer::SetPosX(float vPosX)
{
	m_vPos.x = vPosX;
}
void CPlayer::SetPosY(float vPosY)
{
	m_vPos.y = vPosY;
}
void CPlayer::SetPosZ(float vPosZ)
{
	m_vPos.z = vPosZ;
}

VECTOR CPlayer::GetForcsPos()
{
	VECTOR vHead = { 0 };
	VECTOR vForcus = { 0 };

	//�v���C���[�̓��̍��W���v�Z	
	vHead = VAdd(m_vPos, VGet(0, PLAYER_HEIGHT, 0));

	vHead.y += 10.0f;

	vForcus = vHead;

	return vForcus;
}

void CPlayer::ReflectCollision(VECTOR vAddVec)
{
	//�I�[���[���Ȃ牽�����Ȃ�
	if(vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;

	m_IsJump = false;

	m_vNextPos = VAdd(vAddVec, m_vNextPos);
	
	//�����������͏d�͏��������Ȃ�
	/*m_fGravity = 0.0f;*/
}

//���S���W�擾
void CPlayer::GetCenterPos(VECTOR& vPos)
{
	vPos = VAdd(m_vPos, VGet(0.0f, PLAYER_HALF_HEIGHT, 0.0f));
}

//�����̃T�C�Y���擾
void CPlayer::GetHalfSize(VECTOR& vHalfSize)
{
	vHalfSize = DivVec(m_vSize, 2.0f);
}
