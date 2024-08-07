#include "Title.h"

//��`
const int BACK_X_POS = 640;
const int BACK_Y_POS = 360;
const int TITLE_X_POS = 640;
const int TITLE_Y_POS = 140;
const int START_X_POS = 640;
const int START_Y_POS = 440;
const int FIN_X_POS = 640;
const int FIN_Y_POS = 580;

//�R���X�g���N�^
CTitle::CTitle()
{
	//�\���̂̏�����
	m_sBackImg = {VGet(0.0, 0.0, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(0.0, 0.0, 0.0), -1};			//�w�i�\����
	m_sTitleImg = { VGet(0.0, 0.0, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(0.0, 0.0, 0.0), -1 };			//�^�C�g���\����
	m_sStartImg = { VGet(0.0, 0.0, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(0.0, 0.0, 0.0), -1 };			//�X�^�[�g�\����
	m_sFinImg = { VGet(0.0, 0.0, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(0.0, 0.0, 0.0), -1 };			//�I���\����

	MousePosX = 0;			//�}�E�X��X���W
	MousePosY = 0;			//�}�E�X��Y���W

	m_eSceneID = TITLE_SCENE_INIT;		//�ŏ��ɏ������V�[�������Ă���
}

//�f�X�g���N�^
CTitle::~CTitle()
{
}

void CTitle::Init()
{
	//�\���̂̏�����
	m_sBackImg = { VGet(BACK_X_POS, BACK_Y_POS, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(1.0, 1.0, 1.0), -1 };			//�w�i�\����
	m_sTitleImg = { VGet(TITLE_X_POS, TITLE_Y_POS, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(1.0, 1.0, 1.0), -1 };			//�^�C�g���\����
	m_sStartImg = { VGet(START_X_POS, START_Y_POS, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(1.0, 1.0, 1.0), -1 };			//�X�^�[�g�\����
	m_sFinImg = { VGet(FIN_X_POS, FIN_Y_POS, 0.0),VGet(0.0, 0.0, 0.0) ,VGet(1.0, 1.0, 1.0), -1 };			//�I���\����

	MousePosX = 0;			//�}�E�X��X���W
	MousePosY = 0;			//�}�E�X��Y���W

	m_eSceneID = TITLE_SCENE_INIT;		//�ŏ��ɏ������V�[�������Ă���
}

void CTitle::Load()
{
	//�w�i�摜�ǂݍ���
	if (m_sBackImg.m_iHndl == -1) {
		m_sBackImg.m_iHndl = LoadGraph(TITLE_BACKIMG_PATH);
	}
	//�^�C�g���摜�ǂݍ���
	if (m_sTitleImg.m_iHndl == -1){
		m_sTitleImg.m_iHndl = LoadGraph(TITLE_IMG_PATH);
	}
	//�X�^�[�g�摜�ǂݍ���
	if (m_sStartImg.m_iHndl == -1){
		m_sStartImg.m_iHndl = LoadGraph(TITLE_STARTIMG_PAHT);
	}
	//�I���摜�ǂݍ���
	if (m_sFinImg.m_iHndl == -1){
		m_sFinImg.m_iHndl = LoadGraph(TITLE_FINIMG_PAHT);
	}
}

int CTitle::Loop()
{
	int iRet = 0;
	switch (m_eSceneID)
	{
	case CTitle::TITLE_SCENE_INIT:
		Init();
		m_eSceneID = TITLE_SCENE_LOAD;
		break;
	case CTitle::TITLE_SCENE_LOAD:
		Load();
		m_eSceneID = TITLE_SCENE_LOOP;
		break;
	case CTitle::TITLE_SCENE_LOOP:
		Step();
		Draw();
		break;
	case CTitle::TITLE_SCENE_END:
		Fin();
		m_eSceneID = TITLE_SCENE_INIT;
		iRet = 1;
		break;
	}

	return iRet;
}

void CTitle::Draw()
{
	DrawFormatString(32, 32, GetColor(255, 0, 0), "�^�C�g��");

	DrawRotaGraph(m_sBackImg.m_vPos.x, m_sBackImg.m_vPos.y, 1.0, 0.0, m_sBackImg.m_iHndl, true, false);			//�w�i
	DrawRotaGraph(m_sTitleImg.m_vPos.x, m_sTitleImg.m_vPos.y, 1.0, 0.0, m_sTitleImg.m_iHndl, true, false);		//�^�C�g��
	DrawRotaGraph(m_sStartImg.m_vPos.x, m_sStartImg.m_vPos.y, 1.0, 0.0, m_sStartImg.m_iHndl, true, false);		//�X�^�[�g
	DrawRotaGraph(m_sFinImg.m_vPos.x, m_sFinImg.m_vPos.y, 1.0, 0.0, m_sFinImg.m_iHndl, true, false);			//�I��
}

void CTitle::Step()
{
	//�G���^�[�L�[�������ꂽ��
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		//���̃V�[���ɍs��
		m_eSceneID = TITLE_SCENE_END;
	}
}

void CTitle::Fin()
{
	if (m_sBackImg.m_iHndl != -1) {
		DeleteGraph(m_sBackImg.m_iHndl);
	}
	if (m_sTitleImg.m_iHndl != -1) {
		DeleteGraph(m_sTitleImg.m_iHndl);
	}
	if (m_sBackImg.m_iHndl != -1) {
		DeleteGraph(m_sBackImg.m_iHndl);
	}
	if (m_sStartImg.m_iHndl != -1) {
		DeleteGraph(m_sStartImg.m_iHndl);
	}
	if (m_sBackImg.m_iHndl != -1) {
		DeleteGraph(m_sFinImg.m_iHndl);
	}
}
