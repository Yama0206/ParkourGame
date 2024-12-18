#include "Player.h"

//��`�֘A
static constexpr float VIEWPOINT_SPEED = 0.1f;					//�v���C���[�̉�]���x
static constexpr float MOVE_SPEED = 1.0f;						//�v���C���[�̈ړ����x
static constexpr float ADD_SPEED = 0.2f;						//�v���C���[�̃X�s�[�h�����Z����
static constexpr float SAB_SPEED = 0.1f; 						//�v���C���[�̃X�s�[�h�����Z����
static constexpr float DASH_SPEED = 2.0f;						//�v���C���[�����������̈ړ����x
static constexpr float GRAVITY = 0.2f;							//�v���C���[�̏d��
static constexpr float MAX_GRAVITY = 2.0f;						//�v���C���[�̏d�͂̌��E
static constexpr float MIN_GRAVITY = 0.1f;						//�v���C���[�̏d�͂̍Œ�
static constexpr float YSPEED = 4.5f;							//�v���C���[��Y�����̃X�s�[�h
static constexpr float ROTATE_SPEED = 0.1f;						//��]�X�s�[�h
static constexpr float SCALE = 0.1f;							//�g��k����
	
//�p���N�[���֘A
static constexpr float PARKOUR_MOVE_SPEED = 1.8f;				//�p���N�[���̓���(��)
static constexpr float PARKOUR_JUMP_SPEED = 10.0f;				//�p���N�[���W�����v(��)
static constexpr float PARKOUR_GRAVITY = 0.1f;					//�p���N�[���d��
static constexpr float PARKOUR_MAX_GRAVITY = 1.0f;				//�v���C���[�̏d�͂̌��E

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�ЂƂ܂����������Ă���
	m_sAnimData.m_iID = ANIMID_DEFAULT;				//�v���C���[�̏��
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
	m_sAnimData.m_iID = ANIMID_DEFAULT;				//�v���C���[�̏��
	m_sOldAnimData.m_iID = ANIMID_DEFAULT;			//1F�̃v���C���[�̏��
	m_eDir = FRONT;									//�v���C���[�̕���

	//�ϐ�
	memset(&m_vRot, 0.0f, sizeof(m_vRot));	
	m_vScale = { SCALE , SCALE , SCALE };
	m_PadXBuf = 0;
	m_PadYBuf = 0;
	m_fMoveSpeed = 0.0f;										
	m_fChangeRot = 0.0f;											
	m_fGravity = GRAVITY;											

	//�t���O
	m_bIsHit = false;
	m_bIsHitLength = false;
	m_bIsKeyHit = false;
	m_bIsGround = false;
	m_bIsHide = false;
	m_bIsHitHideObject = false;
	m_bIsParkourObject = false;
	m_bIsPlayAnimation = false;
	m_bIsSpecifiedPos = false;
	m_bIsJump = false;

	m_vPos.y = 10.0f;
}

//���t���[���Ăԏ���
void CPlayer::Step(CShotManager& cShotManager, CCameraManager& cCameraManager)
{
	CDebugManager::GetInstance()->AddFormatString(700, 120, "�v���C���[���W�@X = %f, Y = %f, Z = %f", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugManager::GetInstance()->AddFormatString(700, 140, "�v���C���[��]�l�@X = %f, Y = %f, Z = %f", m_vRot.x, m_vRot.y, m_vRot.z);
	CDebugManager::GetInstance()->AddFormatString(700, 160, "�v���C���[���f����]�l�@X = %f, Y = %f, Z = %f", m_vRot.x, m_vRot.y, m_vRot.z);
	CDebugManager::GetInstance()->AddFormatString(700, 180, "�v���C���[�̒��n�t���O = %d", m_bIsGround);
	CDebugManager::GetInstance()->AddFormatString(700, 200, "�v���C���[�̃X�s�[�h X = %f,Y = %f,Z = %f", m_vSpd.x,m_vSpd.y,m_vSpd.z);
	CDebugManager::GetInstance()->AddFormatString(700, 220, "Pos_Y = %f", m_vNextPos.y);
	CDebugManager::GetInstance()->AddFormatString(700, 240, "�O���r�e�B�[ = %f", m_fGravity);
	CDebugManager::GetInstance()->AddFormatString(700, 320, "�A�j���[�V����ID = %d", m_sAnimData.m_iID);
	CDebugManager::GetInstance()->AddFormatString(700, 340, "�A�j���[�V�����Đ��t���[�� = %f", m_sAnimData.m_fFrm);
	CDebugManager::GetInstance()->AddFormatString(700, 360, "�A�j���[�V�����ŏI�t���[�� = %f", m_sAnimData.m_fEndFrm);
	CDebugManager::GetInstance()->AddFormatString(700, 380, "�A�j���[�V�����Đ���� = %d", m_sAnimData.m_iState);

	if (m_IsAllive) {
		//�v���C���[�̃A�j���[�V��������ۑ����Ă���
		m_sOldAnimData = m_sAnimData;

		//�ړ����Ă��邩�̃`�F�b�N
		m_vNextPos = m_vPos;

		//���X�e�B�b�N�̏����擾
		GetJoypadAnalogInput(&m_PadXBuf, &m_PadYBuf, DX_INPUT_PAD1);

		switch (m_sAnimData.m_iID)
		{
		case ANIMID_DEFAULT:
			ExecDefault();
			break;

		case ANIMID_WAIT:
			ExecWait(cCameraManager.GetPlayCamRot());
			break;

		case ANIMID_RUN:
			ExecRun(cCameraManager.GetPlayCamRot());
			break;

		case ANIMID_FAST_RUN:
			ExecFastRun(cCameraManager.GetPlayCamRot());
			break;

		case ANIMID_JUMP:
			ExecJump(cCameraManager.GetPlayCamRot());
			break;

		case ANIMID_RUNNINGJUMP:
			ExecRunningJump(cCameraManager.GetPlayCamRot());
			break;
		
		case ANIMID_DIVINGJUMP:
			ExecDivingJump();
			break;

		case ANIMID_HIDE:
			ExecHide();
			break;
			
		/*case ANIMID_UPDOWN:
			ExecUpDown();
			break;
		case ANIMID_SHAKE:
			ExecShake();
			break;
		case ANIMID_PIANO:
			ExecPiano();
			break;
		case ANIMID_DANCE:
			ExecDance();
			break;
		*/
		}
		if (CInput::IsKeyKeep(KEY_INPUT_SPACE))
		{
			m_vNextPos.y += 10;
		}

		//�L�[�{�[�h����
		//Control_KeyBord(cCameraManager.GetPlayCamRot());

		//�ړ��ʉ��Z
		AddMove();
	}

	CDebugManager::GetInstance()->AddLine(m_vPos, VAdd(m_vSpd, m_vPos), GetColor(0, 0, 255));

}

void CPlayer::Update()
{
	//1F�O�̃v���C���[�̍��W���X�V����
	m_vPos = m_vNextPos;

	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}

void CPlayer::Draw()
{
	if (m_IsAllive && !m_bIsHide) {
		MV1DrawModel(m_iHndl);
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
		m_bIsKeyHit = false;
	}
}

//����֐�
void CPlayer::Control(VECTOR vRot)
{
	//�L�[�{�[�h����
	Control_KeyBord(vRot);

	//�W�����v����
	Jamp(vRot);
}

//�W�����v����
void CPlayer::Jamp(VECTOR vRot)
{
	//�X�y�[�X�L�[���������Ƃ�
	if (CInput::IsKeyPush(KEY_INPUT_SPACE) && m_bIsGround)
	{
		m_sAnimData.m_iID = ANIMID_JUMP;
	}

	if (m_sAnimData.m_iID == ANIMID_JUMP)
	{
		//m_IsJump = true;
		m_vSpd.y = YSPEED;
	}
}

//�d�͏���
void CPlayer::Gravity()
{
	//�v���C���[�̏d�͂̏��
	//�v���C���[�����̂ɓ������Ă���Ƃ��͏d�͂��~�߂�
	
	if (!m_bIsGround) {
		m_fGravity = GRAVITY;

		if (m_vSpd.y > -MAX_GRAVITY) {
			m_vSpd.y -= m_fGravity;
		}


		CDebugManager::GetInstance()->AddFormatString(700, 0, "�v���C���[�̏d�͂�����O��Y = %f", m_vNextPos.y);
	}
	//�v���C���[��Y���W�Ƀv���C���[��Y�X�s�[�h����
	m_vNextPos.y += m_vSpd.y;

	CDebugManager::GetInstance()->AddFormatString(700, 20, "�v���C���[�̏d�͂����������Ƃ�Y = %f", m_vNextPos.y);
}

void CPlayer::ParkourGravity()
{
	if (!m_bIsGround) {
		m_fGravity = PARKOUR_GRAVITY;

		if (m_vSpd.y > -PARKOUR_MAX_GRAVITY) {
			m_vSpd.y -= m_fGravity;
		}
		CDebugManager::GetInstance()->AddFormatString(700, 0, "�v���C���[�̏d�͂�����O��Y = %f", m_vNextPos.y);
	}

	//�v���C���[��Y���W�Ƀv���C���[��Y�X�s�[�h����
	m_vNextPos.y += m_vSpd.y;
}



void CPlayer::PadControl_AllState()
{
	//�p�b�h�̍��X�e�B�b�N���͂��Ă�����
	if (m_PadXBuf != 0 || m_PadYBuf != 0)
	{
		//R�{�^����������Ă�����
		if (CPad::IsPadKeep(INPUT_R)) {
			//����
			m_sAnimData.m_iID = ANIMID_FAST_RUN;
		}
		else {
			//������
			m_sAnimData.m_iID = ANIMID_RUN;
		}
		
	}
	//A�{�^���������ꂽ��
	else if (CPad::IsPadPush(INPUT_A) && m_bIsGround)
	{
		//�W�����v
		m_sAnimData.m_iID = ANIMID_JUMP;
		m_bIsGround = false;
		
	}
	//�������Ă��Ȃ���
	else {
		//�ҋ@���[�V����
		m_sAnimData.m_iID = ANIMID_WAIT;
	}
}

void CPlayer::PadControl_Run()
{
	//Pad����
	PadControl_AllState();
	if (CPad::IsPadPush(INPUT_A) && m_bIsParkourObject) {
		m_sAnimData.m_iID = ANIMID_DIVINGJUMP;
		m_bIsGround = false;
	}
	else if (CPad::IsPadPush(INPUT_A)) {
		m_sAnimData.m_iID = ANIMID_RUNNINGJUMP;
		m_bIsGround = false;
	}
}

void CPlayer::WaitCalc()
{
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

void CPlayer::RunCalc()
{
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

void CPlayer::FastRunCalc()
{
	//�����������Ă���
	m_fMoveSpeed -= ADD_SPEED;

	//�v���C���[�̃_�b�V���X�s�[�h�̏��
	if (m_fMoveSpeed < -DASH_SPEED) {
		m_fMoveSpeed = -DASH_SPEED;
	}
}

void CPlayer::JumpCalc()
{
	m_bIsGround = false;
	m_vSpd.y = YSPEED;

}


void CPlayer::DivingJumpCalc()
{
	m_bIsGround = false;
	m_vSpd.y = PARKOUR_JUMP_SPEED;
}

//�������Ă��Ȃ��Ƃ�
void CPlayer::ExecDefault()
{
	//��Ԃ̑J�ڂ��������Ȃ�
	//pad�̑���
	PadControl_AllState();

	//�����Ă����Ԃ̎�
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
}

void CPlayer::ExecWait(VECTOR vRot)
{
	//pad�̑���
	PadControl_AllState();

	//�ҋ@��Ԃ̌v�Z����
	WaitCalc();

	//�����Ă����Ԃ̎�
	if (m_sAnimData.m_iID == ANIMID_RUN)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	//�W�����v���Ă�����
	else if (m_sAnimData.m_iID == ANIMID_JUMP)
	{
		Request(ANIMID_JUMP, 1.0f);
		//�W�����v�̌v�Z����
		JumpCalc();
	}
	//�����Ă����Ԃ̎�
	else if (m_sAnimData.m_iID == ANIMID_FAST_RUN)
	{
		RequestLoop(ANIMID_FAST_RUN, 1.0f);
	}
	//�n�C�h���[�h
	if (CPad::IsPadPush(INPUT_B) && m_bIsHitHideObject)
	{
		//�n�C�h���[�h
		m_bIsHide = true;
		m_sAnimData.m_iID = ANIMID_HIDE;
	}

	//���X�e�B�b�N�X���Ńv���C���[����]������
	PadRotation(vRot);

	//�ړ��x�N�g�����v�Z
	CalcMoveVec(vRot);

	//�d�͏���
	Gravity();
}

//�����Ă���Ƃ�
void CPlayer::ExecRun(VECTOR vRot)
{
	//pad�̑���
	PadControl_Run();

	//�������Ԃ̌v�Z����
	RunCalc();

	//�ҋ@���
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
	//�_�b�V�����
	if (m_sAnimData.m_iID == ANIMID_FAST_RUN)
	{
		RequestLoop(ANIMID_FAST_RUN, 1.0f);
	}
	//�����j���O�W�����v
	if (m_sAnimData.m_iID == ANIMID_RUNNINGJUMP)
	{
		RequestLoop(ANIMID_RUNNINGJUMP, 1.0f);
		//�W�����v�v�Z����
		JumpCalc();
	}
	//�_�C�r���O�W�����v
	if (m_sAnimData.m_iID == ANIMID_DIVINGJUMP) {
		//������
		RessetSpeed();
	}

	//�B��鑀��@
	if (CPad::IsPadPush(INPUT_B) && m_bIsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_bIsHide = false;
	}

	//���X�e�B�b�N�X���Ńv���C���[����]������
	PadRotation(vRot);

	//�ړ��x�N�g�����v�Z
	CalcMoveVec(vRot);

	//�d�͏���
	Gravity();
}

//�����Ă���Ƃ�
void CPlayer::ExecFastRun(VECTOR vRot)
{	
	//pad�̑���
	PadControl_Run();

	//�_�b�V����Ԃ̌v�Z����
	FastRunCalc();

	//���_�b�V��
	if (m_sAnimData.m_iID == ANIMID_RUN)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	//�ҋ@���
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
	//�����j���O�W�����v
	if (m_sAnimData.m_iID == ANIMID_RUNNINGJUMP)
	{
		Request(ANIMID_RUNNINGJUMP, 1.0f);
		JumpCalc();
	}
	//�_�C�r���O�W�����v
	if (m_sAnimData.m_iID == ANIMID_DIVINGJUMP) {
	}
	//�B��鑀��
	if (CPad::IsPadPush(INPUT_B) &&  m_bIsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_bIsHide = false;
	}

	//���X�e�B�b�N�X���Ńv���C���[����]������
	PadRotation(vRot);

	//�ړ��x�N�g�����v�Z
	CalcMoveVec(vRot);

	//�d�͏���
	Gravity();
}

void CPlayer::ExecJump(VECTOR vRot)
{
	if (m_bIsGround)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
	}
	
	if (m_bIsGround) {
		//�ʏ킾������
		if (m_sAnimData.m_iID == ANIMID_WAIT) {
			RequestLoop(ANIMID_WAIT, 1.0f);
		}
		//�����Ă�����
		if (m_sAnimData.m_iID == ANIMID_FAST_RUN) {
			RequestLoop(ANIMID_FAST_RUN, 1.0f);
		}
	}

	//���X�e�B�b�N�X���Ńv���C���[����]������
	PadRotation(vRot);

	//�ړ��x�N�g�����v�Z
	CalcMoveVec(vRot);

	//�d�͏���
	Gravity();
}

void CPlayer::ExecRunningJump(VECTOR vRot)
{
	if (m_bIsGround)
	{
		//pad�̑���
		PadControl_AllState();
	}
	//pad�̑���
	//�_�b�V����Ԃ̌v�Z����
	if (m_sOldAnimData.m_iID == ANIMID_FAST_RUN) {
		FastRunCalc();
	}
	if (m_sOldAnimData.m_iID == ANIMID_RUN) {
		RunCalc();
	}

	if (m_bIsGround) {
		//�ʏ킾������
		if (m_sAnimData.m_iID == ANIMID_WAIT) {
			RequestLoop(ANIMID_WAIT, 1.0f);
		}
		//���_�b�V��
		if (m_sAnimData.m_iID == ANIMID_RUN) {
			RequestLoop(ANIMID_RUN, 1.0f);
		}
		//�_�b�V��
		if (m_sAnimData.m_iID == ANIMID_FAST_RUN) {
			RequestLoop(ANIMID_FAST_RUN, 1.0f);
		}
	}

	//���X�e�B�b�N�X���Ńv���C���[����]������
	PadRotation(vRot);

	//�ړ��x�N�g�����v�Z
	CalcMoveVec(vRot);

	//�d�͏���
	Gravity();
}

void CPlayer::ExecDivingJump()
{
	//�X�s�[�h������
	memset(&m_vSpd, 0.0f, sizeof(VECTOR));
	//�p���N�[�����߂̏���
	ParkourBegin(VGet(100.0f, 0.0f, 100.0f), VGet(1.0f, 0.0f, 1.0f));

	//�w��̏ꏊ�ɂ��Ă�����
	if (m_bIsSpecifiedPos) {
		//�A�j���[�V�������Đ�����Ă��Ȃ�������
		if (!m_bIsPlayAnimation) {
			//�p���N�[���A�j���[�V�������N�G�X�g
			Request(ANIMID_DIVINGJUMP, 1.6f);
			//�A�j���[�V�����Đ��t���OON
			m_bIsPlayAnimation = true;
		}
		//�A�j���[�V�������I��������
		if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
		{
			//�A�j���[�V�����Đ��t���O��OFF�ɂ���
			m_bIsPlayAnimation = false;
		}

		if (!m_bIsJump)
		{
			//�W�����v����
			DivingJumpCalc();
			m_bIsJump = true;
		}
		//�A�j���[�V�������I���܂ł̊�
		if (m_sAnimData.m_fFrm < m_sAnimData.m_fEndFrm) {
			m_vSpd.x = PARKOUR_MOVE_SPEED;
			m_vSpd.z = PARKOUR_MOVE_SPEED;
		}

		//�A�j���[�V�������I�������
		else {
			//�W�����v�t���O��false�ɂ���
			m_bIsJump = false;

			//pad�̑���
			PadControl_AllState();
		}
	}

	//�ʏ킾������
	if (m_sAnimData.m_iID == ANIMID_WAIT) {
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
	//���_�b�V��
	if (m_sAnimData.m_iID == ANIMID_RUN) {
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	//�_�b�V��
	if (m_sAnimData.m_iID == ANIMID_FAST_RUN) {
		RequestLoop(ANIMID_FAST_RUN, 1.0f);
	}

	//�d�͏���
	ParkourGravity();
}

void CPlayer::ExecHide()
{
	memset(&m_vSpd, 0.0f, sizeof(m_vSpd));
	m_fMoveSpeed = 0.0f;

	if (CPad::IsPadPush(INPUT_B) && m_bIsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_bIsHide = false;
	}

	CDebugManager::GetInstance()->AddFormatString(700, 450, "�n�C�h���[�h");
}

void CPlayer::PadRotation(VECTOR vCameraRot)
{
	//���X�e�B�b�N���X���Ă���Ƃ�
	if (m_PadXBuf != 0 || m_PadYBuf != 0) {
		//�X�e�B�b�N�̊p�x�ɍ��킹�ăv���C���[����]
		m_fRot = atan2f((float)m_PadXBuf * -1, (float)m_PadYBuf);
		//�v���C���[����]
		m_vRot.y = vCameraRot.y + m_fRot;
	}
}

void CPlayer::CalcMoveVec(VECTOR vCameraRot)
{
	//�ړ��x�N�g���v�Z
	m_vSpd.x = sinf(vCameraRot.y + m_fRot) * m_fMoveSpeed;
	m_vSpd.z = cosf(vCameraRot.y + m_fRot) * m_fMoveSpeed;
}

void CPlayer::AddMove()
{
	//�ړ����x�����݂̍��W�ɉ��Z����
	m_vNextPos.x += m_vSpd.x;
	m_vNextPos.y += m_vSpd.y;
	m_vNextPos.z += m_vSpd.z;
}

void CPlayer::RessetSpeed()
{
	m_fMoveSpeed = 0.0f;
	memset(&m_vSpd, 0.0f, sizeof(m_vSpd));
}

void CPlayer::ParkourMotion(VECTOR vPos, float Gravity)
{

}

void CPlayer::ParkourBegin(VECTOR vStartPos, VECTOR vSpd)
{
	VECTOR TwoPoint;

	//�w��̏ꏊ�Ɉړ�
	m_vNextPos = VAdd(m_vNextPos, MoveIocationSpecification(m_vNextPos, vStartPos));


	TwoPoint = RotetoSpecifiedPos(vStartPos, m_vNextPos, m_vRot, vSpd, 0.08f);

	if (TwoPoint.x <= 1.0f && TwoPoint.y <= 1.0f && TwoPoint.z <= 1.0f)
	{
		m_bIsSpecifiedPos = true;
	}
	else {
		m_bIsSpecifiedPos = false;
	}
}

void CPlayer::ParkourMiddle()
{
	
}

void CPlayer::ParkourFin()
{

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

	if (vAddVec.y != 0.0f) {
		m_bIsGround = true;
	}

	CDebugManager::GetInstance()->AddFormatString(700, 60, "���f���̂����蔻��O��Y = %f", m_vNextPos.y);

	m_vNextPos = VAdd(vAddVec, m_vNextPos);
	
	CDebugManager::GetInstance()->AddFormatString(700, 80, "���f���̂����蔻����Y = %f", m_vNextPos.y);
	MV1SetPosition(m_iHndl, m_vNextPos);

	//�����������͏d�͏��������Ȃ�
	m_fGravity = 0.0f;
}

void CPlayer::Control_KeyBord(VECTOR vRot)
{
	//�L�[�{�[�h
	//W�L�[�������ꂽ�Ƃ�
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		//�����Ă���
		m_sAnimData.m_iID = ANIMID_RUN;

		//�L�[�������ꂽ�t���OON
		m_bIsKeyHit = true;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l������
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = DX_PI_F;
		//���f������]������
		m_vRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		//�����Ă���
		m_sAnimData.m_iID = ANIMID_RUN;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			//����
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = 0.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_vRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		//�����Ă���
		m_sAnimData.m_iID = ANIMID_RUN;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l������
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		//��]�l
		m_fRot = 90.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_vRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D))
	{
		//�����Ă���
		m_sAnimData.m_iID = ANIMID_RUN;

		//���W�ړ�
		m_fMoveSpeed -= ADD_SPEED;

		//�ő�l
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = -90.0f * DX_PI_F / 180.0f;

		//�����Ă������
		m_vRot.y = vRot.y + m_fRot;
	}
	else {
		m_sAnimData.m_iID = ANIMID_WAIT;
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

VECTOR CPlayer::MoveIocationSpecification(VECTOR _startPos, VECTOR _endPos)
{
	//�Ԃ��l
	VECTOR Vec;

	//�x�N�g���𐶐�
	Vec = VecCreate(_startPos, _endPos);

	//���K��
	Vec = NormalizeVec(Vec);

	return Vec;
}

VECTOR CPlayer::RotetoSpecifiedPos(VECTOR vEndPos ,VECTOR vStartPos, VECTOR& vRot, VECTOR vSpd, float RotetoSpd)
{
	//�p���N�[�����n�܂�����X�^�[�g������W�Ɍ����킹��
	//�z�[�~���O����
	VECTOR StartPosVec;
	//�v���C���[����w��̏ꏊ�Ɍ������x�N�g��
	StartPosVec.x = vEndPos.x - vStartPos.x;
	StartPosVec.y = 0.0f;
	StartPosVec.z = vEndPos.z - vStartPos.z;

	float fCrossZ = 0.0f;

	//���݂̐i�s�����̃x�N�g��
	VECTOR  MoveVec;

	memset(&MoveVec, 0.0f, sizeof(MoveVec));

	MoveVec.x = sinf(vRot.y) * -vSpd.x;
	MoveVec.y = 0.0f;
	MoveVec.z = cosf(vRot.y) * -vSpd.z;

	//2�̃x�N�g���̊O�ς��v�Z
	fCrossZ = StartPosVec.x * MoveVec.z - MoveVec.x * StartPosVec.z;

	//fCrossZ�̌v�Z���ʂō��E�̔�����s��
	if (fabsf(fCrossZ) <= 10.0f)
	{
		vRot.y = atan2f(-StartPosVec.x, -StartPosVec.z);
		CDebugManager::GetInstance()->AddFormatString(700, 540, "�v���C���[�͐���");
	}
	else if (fCrossZ > 0)
	{
		vRot.y += RotetoSpd;
		CDebugManager::GetInstance()->AddFormatString(700, 520, "�v���C���[�͍�");
	}
	else if (fCrossZ < 0)
	{
		vRot.y -= RotetoSpd;
		CDebugManager::GetInstance()->AddFormatString(700, 500, "�v���C���[�͉E");
	}

	CDebugManager::GetInstance()->AddFormatString(700, 600, "���E����̒l = %f", fCrossZ);
	CDebugManager::GetInstance()->AddFormatString(700, 620, "�i�s�����x�N�g�� X = %f, Y = %f, Z = %f", MoveVec.x, MoveVec.y, MoveVec.z);
	CDebugManager::GetInstance()->AddFormatString(650, 640, "�X�^�[�g������W�܂ł̋��� X = %f, Y = %f, Z = %f", StartPosVec.x, StartPosVec.y, StartPosVec.z);
	CDebugManager::GetInstance()->AddLine(m_vPos, VAdd(MoveVec, m_vPos), GetColor(0, 255, 0));
	CDebugManager::GetInstance()->AddLine(m_vPos, vStartPos);


	return StartPosVec;
}