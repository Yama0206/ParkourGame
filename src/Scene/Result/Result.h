#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"

const char RESULT_IMG_PATH[] = { "" };

class CResult
{
private:
	enum tagRESULT_SCENE {
		RESULT_SCENE_INIT,
		RESULT_SCENE_LOAD,
		RESULT_SCENE_LOOP,
		RESULT_SCENE_END,

		RESULT_SCENE_NUM
	};

	tagRESULT_SCENE m_eSceneID;				//�V�[���ۑ�

	VECTOR m_vPos;
	int m_ImgHndl;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CResult();
	~CResult();


	//�J��Ԃ��s������
	int Loop();
	//�`�揈��
	void Draw();

private:
	//������
	void Init();
	//�I������
	void Fin();
	//�f�[�^���[�h
	void Load();
	//���t���[��
	void Step();
};

