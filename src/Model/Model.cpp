#include "Model.h"


//������
void CModel::Init()
{
	Exit();
	//�ЂƂ܂����������Ă���
	memset(&m_vPos, 0.0f, sizeof(VECTOR));			//���W
	memset(&m_vNextPos, 0.0f, sizeof(VECTOR));		//�X�V��̍��W
	memset(&m_vRot, 0.0f, sizeof(VECTOR));			//��]���x
	memset(&m_vSpd, 0.0f, sizeof(VECTOR));			//����
	memset(&m_vScale, 0.0f, sizeof(VECTOR));		//�g��k����
	memset(&m_vSize, 0.0f, sizeof(VECTOR));			//�c�A���A���s��	
	memset(&m_IsAllive, true, sizeof(bool));		//�����t���O
	m_iHndl = -1;									//�v���C���[�̃��f���n���h��

	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	ZeroMemory(&m_sOldAnimData, sizeof(m_sOldAnimData));
	m_sAnimData.m_iHndl = -1;						//�A�j���f�[�^�̃��f���n���h��
	m_sAnimData.m_iID = -0;							//�A�j���f�[�^�̃A�j���ԍ�
	m_sOldAnimData.m_iHndl = -1;					//�X�V�O�̃A�j���f�[�^�̃��f���n���h��
	m_sOldAnimData.m_iID = -0;						//�X�V�O�̃A�j���f�[�^�̃A�j���ԍ�
}

//�I������
void CModel::Exit()
{
	DeleteModel();
}

//�X�V����
void CModel::Update()
{
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);
}

bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1) {
		return false;				//���f���̓ǂݍ��ݍς�
	}
	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1) {
		return false;				//���f���̓ǂݍ���
	}
	return true;
}

void CModel::Draw()
{

}

//�R�s�[�f�[�^�ǂݍ���
bool CModel::DupilicateModel(int iSrcHndl)
{
	if (m_iHndl != -1) {
		return false;				//���f���ǂݍ��ݍς�
	}
	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1) {
		return false;				//���f���ǂݍ��ݎ��s
	}

	return true;
}

void CModel::DeleteModel()
{
	if (m_iHndl == -1)
	{
		return;
	}
	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//�A�j�����N�G�X�g
void CModel::Request(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	//�A�j���[�V�����Ń^�b�`
	DetachAnim();

	//�A�j���Đ�&�e��f�[�^���Z�b�g
	m_sAnimData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimID, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_iID = iAnimID;
	m_sAnimData.m_fEndFrm = MV1GetAnimTotalTime(m_iHndl, iAnimID);
	m_sAnimData.m_fFrm = 0.0f;
	m_sAnimData.m_fSpd = fAnimSpd;
	m_sAnimData.m_iState = ANIMSTATE_NORMAL;
}

//���[�v���N�G�X�g
void CModel::RequestLoop(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, fAnimSpd, iAnimSrcHndl, NameCheck);
	//�����������[�v����
	m_sAnimData.m_iState = ANIMSTATE_LOOP;
}

//�G���h���[�v���N�G�X�g
void CModel::RequestendLoop(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, fAnimSpd, iAnimSrcHndl, NameCheck);
	//���������G���h���[�v�ɕς���
	m_sAnimData.m_iState = ANIMSTATE_END;
}


//�A�j���[�V�����f�^�b�`
void CModel::DetachAnim()
{
	if (m_sAnimData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimData.m_iHndl);
		m_sAnimData.m_iHndl = -1;
	}
}

void CModel::UpdateBlendRate()
{
	if (m_sOldAnimData.m_iID != -1) {

		m_sAnimData.m_fRate += 0.1f;

		MV1SetAttachAnimBlendRate(m_iHndl, m_sOldAnimData.m_iID, 1.0 - m_sAnimData.m_fRate);
		MV1SetAttachAnimBlendRate(m_iHndl, m_sAnimData.m_iID, m_sAnimData.m_fRate);

		if (m_sAnimData.m_fRate >= 1.0f) {
			MV1DetachAnim(m_iHndl, m_sOldAnimData.m_iID);
			m_sOldAnimData.m_iID = -1;
		}
	}
}

//�A�j���A�b�v�f�[�^
void CModel::UpdateAnim()
{
	if (m_sAnimData.m_iHndl == -1) { return; }	//�A�j���[�V�������Đ�����Ă��Ȃ�

	//�A�j���[�V�������x�X�V
	m_sAnimData.m_fFrm += m_sAnimData.m_fSpd;

	if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
	{
		//�ŏI�t���[���܂ŗ�����A��Ԃɍ��킹�ē����ς���
		switch (m_sAnimData.m_iState)
		{
		//�ʏ�͏I��������
		case ANIMSTATE_NORMAL:
			DetachAnim();
			m_sAnimData.m_fEndFrm = 0.0f;
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_fSpd = 0.0f;
			return;
			//���[�v�����f��
		case ANIMSTATE_LOOP:
			m_sAnimData.m_fFrm = 0.0f;
			break;
			//�G���h���[�v�Ō�Ŏ~�߂�
		case ANIMSTATE_END:
			m_sAnimData.m_fFrm = m_sAnimData.m_fEndFrm;
			break;
		}
	}

	//�Đ����Ԑݒ�
	MV1SetAttachAnimTime(m_iHndl, m_sAnimData.m_iHndl, m_sAnimData.m_fFrm);
}