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
	m_cField.Init();				//������
	m_cField.UpDate();				//�X�V����
	//��
	m_cSky.Init();					//������
	m_cSky.UpDate();				//�X�V����

	//�p���N�[���I�u�W�F�N�g
	CParkourObjectManager::GetInstance()->Init();			//������
	CParkourObjectManager::GetInstance()->Update();			//�X�V����

	//�S�[��������
	cGoal.Init();

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Init();
	}

	m_cLocker[0].SetPos(VGet(-231.1f, -1.0f, -135.0f));
	m_cLocker[1].SetPos(VGet(-429.0f, -1.0f, -467.0f));
	m_cLocker[2].SetPos(VGet(-556.0f, -1.0f, -671.0f));

	//�T�E���h�֘A
	CSoundManager::Init();
	//CSoundManager::LoadAllData();

	cBox.Init();
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

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Load();
	}

	cBox.Load();
}

//���t���[���Ăԏ���
void CPlayScene::Step()
{
	//��ƂȂ�f�o�b�O�֘A��\�������Ă���
	CDebugManager::GetInstance()->AddBox(VGet(0, 10, 0), VGet(1, 1, 1));

	CDebugManager::GetInstance()->AddSphere(VGet(30, 10, 0), 1);

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

		CCheckPointManager::GetInstance()->Step();

		if (m_cPlayer.GetIsHide())
		{
			m_cEnemyManager.SetIsPlayerHideMode(true);
		}
		else {
			m_cEnemyManager.SetIsPlayerHideMode(false);
		}
		
		cBox.Step();

		//�����蔻�菈��

		CCollisionManager::CHeckHitPlayerToGoal(m_cPlayer, cGoal);
		CCollisionManager::CheckHitPlayerToItem(m_cPlayer, m_cItemManager);
		for (int i = 0; i < 3; i++) {
			CCollisionManager::CheckHitPlayerToHideObject(m_cPlayer, m_cLocker[i]);
		}
		CCollisionManager::CheckHitEnemyToPoint(m_cEnemyManager);
		CCollisionManager::CheckHitPlayerToEnemy(m_cPlayer, m_cEnemyManager);
		CCollisionManager::CheckHitPlayerToPoint(m_cPlayer, m_cEnemyManager);
		CCollisionManager::CheckHitFieldToPlayer(m_cPlayer, m_cField);
		CCollisionManager::CheckHitEnemyToField(m_cEnemyManager, m_cField);
		CCollisionManager::CheckHitPlayerToParkourObject(m_cPlayer, cBox);
		
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

		for (int i = 0; i < 3; i++) {
			m_cLocker[i].Update();
		}

		cBox.Update();
	}

	//�J�����؂�ւ�����
	if (CInput::IsKeyPush(KEY_INPUT_C))
	{
		//�J�����}�l�[�W���[
		m_cCameraManager.Step(m_cPlayer.GetForcsPos(), m_cPlayer.GetRotate());
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_DEBUG);
	}
	else if (CInput::IsKeyPush(KEY_INPUT_V))
	{
		//�f�o�b�O���[�h
		m_cCameraManager.ChangeCamera(CCameraManager::CAMERA_ID_PLAY);
	}

	//�G���^�[�L�[����������
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		//�v���C�̃G���h�V�[��
		m_eSceneID = PLAY_SCENE_END;
	}

	//�J�����X�V����
	m_cCameraManager.Step(m_cPlayer.GetForcsPos(), m_cPlayer.GetSpd());

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
	//m_cSky.Draw();				//��`��
	cGoal.Draw();					//�S�[���`��

	cBox.Draw();

	for (int i = 0; i < 3; i++) {
		m_cLocker[i].Draw();
	}

	//�f�o�b�O
	CDebugManager::GetInstance()->Draw();
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