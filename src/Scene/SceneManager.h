#pragma once

#include "Play/ScenePlay.h"
#include "Title/Title.h"
#include "Result/Result.h"
#include "Clear/Clear.h"

class SceneManager
{
private:
	enum tagSCENE {
		SCENE_TITLE,	//�^�C�g�����
		SCENE_PLAY,		//�Q�[����
		SCENE_RESULT,	//���U���g���
		SCENE_CLEAR,	//�N���A���

		SCENE_NUM
	};

	CPlayScene cPlayScene;		//�v���C�V�[��
	CTitle	   cTitle;			//�^�C�g���V�[��
	CResult    cResult;			//���U���g�V�[��
	CClear     cClear;
	tagSCENE m_eSceneID;		//�V�[���ۑ�

public:
	//�R���X�g���N�^
	SceneManager();

	//�J��Ԃ��s������
	void Loop();

	//�`�揈��
	void Draw();
};

