#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"

const char CLEAR_IMG_PATH[] = { "" };

class CClear {
private:
	enum tagCLEAR_SCENE {
		CLEAR_SCENE_INIT,
		CLEAR_SCENE_LOAD,
		CLEAR_SCENE_LOOP,
		CLEAR_SCENE_END,

		CLEAR_SCENE_NUM
	};

	tagCLEAR_SCENE m_eSceneID;				//�V�[���ۑ�

	VECTOR m_vPos;
	int m_ImgHndl;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CClear();
	~CClear();


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
