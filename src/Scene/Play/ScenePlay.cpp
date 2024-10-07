#include "ScenePlay.h"

//��`�֘A


//�R���X�g���N�^
CPlayScene::CPlayScene()
{
	//�ЂƂ܂����������Ă���
	m_eSceneID = PLAY_SCENE_INIT;
}

CPlayScene::~CPlayScene() {

}

int CPlayScene::Loop()
{
	int iRet = 0;
	//�����͂ЂƂ܂�switch���𗘗p����
	switch (m_eSceneID)
	{
	case CPlayScene::PLAY_SCENE_INIT:
		Init();
		m_eSceneID = PLAY_SCENE_LOAD;
		break;
	case CPlayScene::PLAY_SCENE_LOAD:
		Load();
		CSoundManager::Play(CSoundManager::SOUNDID_BGM, DX_PLAYTYPE_LOOP);
		m_eSceneID = PLAY_SCENE_LOOP;
		break;
	case CPlayScene::PLAY_SCENE_LOOP:
		Step();
		break;
	case CPlayScene::PLAY_SCENE_END:
		iRet = Fin();
		m_eSceneID = PLAY_SCENE_INIT;
		break;
	}

	return iRet;
}

//������
void CPlayScene::Init()
{
	//�J�E���g�ϐ�������
	m_TimeCnt = 0;
	m_FreamCnt = 0;

	//�J�����̏�����
	m_cCameraManager.Init();
	m_cCameraManager.SetNearFar(5.0f, 10000.0f);
	//�v���C���[������
	m_cPlayer.Init();
	m_cPlayer.InitValue();
	m_cPlayer.SetSize();
	//�G������
	m_cEnemyManager.Init();
	//�I�u�W�F�N�g
	m_cObjectManager.Init();		//������
	m_cObjectManager.Update();		//�X�V����
	//�A�C�e��
	m_cItemManager.Init();			//������
	//�e�̏�����
	m_cShotManager.Init();			//������
	//�w�i
	m_cField.Init();			//������
	m_cField.UpDate();			//�X�V����
	//��
	m_cSky.Init();					//������
	m_cSky.UpDate();				//�X�V����

	cFBox.resize(FBOX_MAX_NUM);
	cRock.resize(FBOX_MAX_NUM);

	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		cFBox[FBoxIndex].Init();		//����̔�
	}
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++)
	{
		cRock[RockIndex].Init();
	}

	//�S�[��������
	cGoal.Init();

	//SetBlock();

	//�T�E���h�֘A
	CSoundManager::Init();
	//CSoundManager::LoadAllData();
}

//�I������
int CPlayScene::Fin()
{
	int iRet = 0;
	if (cGoal.GetIsGoal() == true)
	{
		iRet = 1;
	}
	else {
		iRet = 2;
	}

	m_cCameraManager.Fin();			//�J�����}�l�[�W���[
	m_cPlayer.Fin();				//�v���C���[
	m_cEnemyManager.Fin();			//�G
	m_cObjectManager.Fin();			//�I�u�W�F�N�g
	m_cField.Fin();					//�w�i
	m_cSky.Fin();					//��

	//�T�E���h�֘A
	CSoundManager::Exit();
	
	return iRet;
}

//�ǂݍ���
void CPlayScene::Load()
{
	m_cPlayer.LoadModel(PLAYER_MODEL_PATH);						//�v���C���[
	m_cEnemyManager.Load();										//�G
	m_cObjectManager.Load();									//�I�u�W�F�N�g
	m_cItemManager.Load();										//�A�C�e��
	m_cShotManager.Load();										//�e
	m_cField.Load();											//�w�i
	m_cSky.Load();												//��
	CCheckPointManager::GetInstance()->Load();					//�`�F�b�N�|�C���g

	//�S�[���ǂݍ���
	cGoal.Load();
}

//���t���[���Ăԏ���
void CPlayScene::Step()
{
	
	//�v���C���[�X�V����
	if (m_cCameraManager.GetCameraID() == CCameraManager::CAMERA_ID_PLAY)
	{
		//�v���C���[
		m_cPlayer.Step(m_cShotManager, m_cCameraManager);
		//�G
		m_cEnemyManager.Step(m_cPlayer.GetPosition());
		//�e
		m_cShotManager.Step();
		
		//��̒ʏ폈��
		m_cSky.Step();

		//�����蔻�菈��
		CCollisionManager::CheckHitShotToEnemy(m_cEnemyManager, m_cShotManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CHeckHitPlayerToGoal(m_cPlayer, cGoal);
		CCollisionManager::CheckHitPlayerToItem(m_cPlayer, m_cItemManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CheckHitEnemyToPoint(m_cEnemyManager);
		//CollisionManager::CheckHitPlayerToPoint(m_cPlayer, m_cCheckPointManager);
		
		//�X�V����--------------------------------------------------------------//
		//�v���C���[
		m_cPlayer.Update();	
		//�G
		m_cEnemyManager.Update();
		//�A�j���[�V����
		m_cPlayer.UpdateAnim();	
		//�V��
		m_cSky.UpDate();
		//�S�[��
		cGoal.Update();			
		//�A�C�e��
		m_cItemManager.Update();
	}

	//�J�����؂�ւ�����
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		//�J�����}�l�[�W���[
		m_cCameraManager.Step(m_cPlayer.GetPosition(), m_cPlayer.GetRotate());
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{

		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	}

	//�G���^�[�L�[����������
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		//�v���C�̃G���h�V�[��
		m_eSceneID = PLAY_SCENE_END;
	}

	//�J�����X�V����
	m_cCameraManager.Step(m_cPlayer.GetPosition(), m_cPlayer.GetSpd());

	//�v���C���[�����S������
	GameEnd();
}

//�v���C���[�����S�����ꍇ�̏���
void CPlayScene::GameEnd()
{
	if (m_cPlayer.GetIsAllive() == false)
	{
		m_eSceneID = PLAY_SCENE_END;
	}
	if (m_cPlayer.GetIsAllive() == true && cGoal.GetIsGoal() == true)
	{
		m_eSceneID = PLAY_SCENE_END;
	}
}


//�X�V����
void CPlayScene::Draw()
{
	m_cPlayer.Draw();				//�v���C���[�`��
	m_cEnemyManager.Draw();			//�G�̕`��
	m_cItemManager.Draw();			//�A�C�e���̕`��
	m_cShotManager.Draw();			//�e�̕`��
	m_cField.Draw();				//�w�i�`��
	//m_cSky.Draw();					//��`��
	cGoal.Draw();					//�S�[���`��
	m_cDebug.PrintSpeed(32, 32, m_cPlayer.GetfSpd());
	m_cDebug.PrintSpeed(100, 100, m_cPlayer.m_fMoveSpeed);
	m_cDebug.PrintSpeed(100, 150, m_cPlayer.GetSpd().z);

	m_cDebug.PrintPos(500, 32, m_cEnemyManager.GetPosVec(0));
	m_cDebug.PrintPos(300, 32, CCheckPointManager::GetInstance()->GetPosVec(0));
	m_cDebug.PrintPos(300, 42, CCheckPointManager::GetInstance()->GetPosVec(1));
	m_cDebug.PrintPos(300, 52, CCheckPointManager::GetInstance()->GetPosVec(2));
	m_cDebug.PrintPos(300, 62, CCheckPointManager::GetInstance()->GetPosVec(3));
	//�G�l�~�[�N���X�擾
	CEnemy* cEnemy = m_cEnemyManager.GetEnemy(0);
	m_cDebug.PrintNum(500, 42, cEnemy->GetCPNum());
	

	//for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
	//	cRock[RockIndex].Draw();
	//}
}

void CPlayScene::SetBlock()
{
	//����@��
	m_vFBoxPos[0] = { 0.0f, 0.0f, 0.0f };
	m_vFBoxPos[1] = { 0.0f, 0.0f, 60.0f };
	m_vFBoxPos[2] = { 30.0f, 0.0f, 120.0f };
	m_vFBoxPos[3] = { 0.0f, 20.0f, 180.0f };
	m_vFBoxPos[4] = { 0.0f, 0.0f, 240.0f };
	m_vFBoxPos[5] = { 0.0f, 0.0f, 300.0f };
	m_vFBoxPos[6] = { 0.0f, 0.0f, 360.0f };
	m_vFBoxPos[7] = { 60.0f, 0.0f, 440.0f};
	m_vFBoxPos[8] = { 30.0f, 30.0f, 480.0f };
	m_vFBoxPos[9] = { 80.0f, 0.0f, 500.0f };
	m_vFBoxPos[10] = { 0.0f, 0.0f, 510.0f };
	m_vFBoxPos[11] = { 0.0f, 25.0f, 560.0f };
	m_vFBoxPos[12] = { 0.0f, 40.0f, 600.0f };
	m_vFBoxPos[13] = { 0.0f, 25.0f, 660.0f };
	m_vFBoxPos[14] = { 0.0f, 0.0f, 700.0f };
	m_vFBoxPos[15] = { 0.0f, 0.0f, 730.0f };

	for (int i = 0; i < FBOX_MAX_NUM; i++)
	{
		cFBox[i].Init(m_vFBoxPos[i], m_vFBoxSize[i], m_vFBoxRot[i]);
	}

	//����@��
	m_vRockPos[0] = { 0.0f, 0.0f, 0.0f };
	m_vRockPos[1] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[2] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[3] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[4] = { 0.0f, 0.0f, 100.0f };
	m_vRockPos[5] = { 0.0f, 0.0f, 100.0f };


	for (int i = 0; i < cRock.size(); i++)
	{
		cRock[i].Init(m_vRockPos[i], m_vRockScale[i]);
	}
}

void CPlayScene::TimeCnt()
{
	m_FreamCnt++;

	if (m_FreamCnt >= 60)
	{
		m_TimeCnt++;
		m_FreamCnt = 0;
	}

}