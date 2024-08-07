#include "SceneManager.h"

//��`�֘A


//�R���X�g���N�^
SceneManager::SceneManager()
{
	//�ŏ��̓^�C�g����ʂ�
	m_eSceneID = SCENE_TITLE;
}

void SceneManager::Loop()
{
	//�S�[�����������S���������肷��
	int End = 0;

	//�����͂ЂƂ܂�switch���𗘗p����
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		//�^�C�g���̃G���h�V�[���܂ŗ�����
		if (cTitle.Loop() != 0) 
		{
			//�v���C�V�[���Ɉړ�����
			m_eSceneID = SCENE_PLAY;
		}
		break;
	case SceneManager::SCENE_PLAY:
		//�v���C�̃G���h�܂ŗ�����
		End = cPlayScene.Loop();
		if(End == 2)
		{
			//���U���g�V�[���ɍs��
			m_eSceneID = SCENE_RESULT;
		}
		else if(End == 1){
			//�N���A�V�[���ɍs��
			m_eSceneID = SCENE_CLEAR;
		}
		break;
	case SceneManager::SCENE_RESULT:
		if (cResult.Loop() != 0)
		{
			//�^�C�g���V�[���ɍs��
			m_eSceneID = SCENE_TITLE;
		}
		break;
	case SceneManager::SCENE_CLEAR:
		if (cClear.Loop() != 0)
		{
			//�^�C�g���V�[���ɍs��
			m_eSceneID = SCENE_TITLE;
		}
		break;
	}
}

//�X�V����
void SceneManager::Draw()
{
	switch (m_eSceneID)
	{
	case SceneManager::SCENE_TITLE:
		cTitle.Draw();
		break;
	case SceneManager::SCENE_PLAY:
		cPlayScene.Draw();
		break;
	case SceneManager::SCENE_RESULT:
		break;
	case SceneManager::SCENE_CLEAR:
		break;
	}
}
