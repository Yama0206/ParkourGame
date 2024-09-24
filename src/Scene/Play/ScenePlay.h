#pragma once
#include "DxLib.h"
#include <vector>
#include <iostream>
#include "../../Input/Input.h"
#include "../../Camera/CameraManager.h"
#include "../../Player/Player.h"
#include "../../Field/Field.h"
#include "../../shot/ShotManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Object/ObjectManager.h"
#include "../../Collision/CollisionManager.h"
#include "../../System/Sound/SoundManager.h"
#include "../../Field/Sky/Sky.h"
#include "../../Box/Box.h"
#include "../../Box/FootBox.h"
#include "../../Box/Rock.h"
#include "../../Goal/Goal.h"
#include "../../Item/Manager/ItemManager.h"

using namespace std;

class CPlayScene
{
private:
	enum tagPLAY_SCENE {
		PLAY_SCENE_INIT,
		PLAY_SCENE_LOAD,
		PLAY_SCENE_LOOP,
		PLAY_SCENE_END,

		PLAY_SCENE_NUM
	};

	CCameraManager m_cCameraManager;			//�J�����}�l�[�W���[
	CShotManager m_cShotManager;				//�e�̔���
	CPlayer m_cPlayer;							//�v���C���[����
	CEnemyManager m_cEnemyManager;				//�G
	CObjectManager m_cObjectManager;			//�I�u�W�F�N�g
	CItemManager m_cItemManager;				//�A�C�e���}�l�[�W���[
	BackGround m_cBackGround;					//�w�i����
	CSky m_cSky;								//��
	tagPLAY_SCENE m_eSceneID;					//�V�[���ۑ�

	//��
	CBox cBox;		//��
	vector<CFootBox> cFBox;	//����̔�
	vector<CRock>    cRock;	//����̐�
	CGoal			 cGoal;	//�S�[��

	vector<VECTOR> m_vFBoxPos;			//����̔��̍��W
	vector<VECTOR> m_vFBoxSize;			//����̔��̑傫��
	vector<VECTOR> m_vFBoxRot;			//����̔��̊p�x
	vector<VECTOR> m_vRockPos;			//����̐΂̍��W
	vector<VECTOR> m_vRockScale;		//����̐΂̑傫��
	vector<VECTOR> m_vRockRot;			//����̐΂̊p�x

	//�v���C���Ԃ��J�E���g����p�̕ϐ�
	int m_TimeCnt;
	//�v���C��ʂ̃t���[�����J�E���g����ϐ�
	int m_FreamCnt;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayScene();
	~CPlayScene();


	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();

private:
	//������
	void Init();
	//�I������
	int Fin();
	//�f�[�^���[�h
	void Load();
	//���t���[��
	void Step();

	//�v���C���[�̎��S����
	void GameEnd();

	//�u���b�N��ݒu
	void SetBlock();

	//�v���C���Ԃ��J�E���g����֐�
	void TimeCnt();

};
