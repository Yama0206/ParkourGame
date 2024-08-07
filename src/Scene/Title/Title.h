#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"
#include "../../Collision/CollisionManager.h"

//��`
const char TITLE_BACKIMG_PATH[] = { "data/Title/�Q�[���ۑ�@�^�C�g�����.png" };		//�w�i�摜�p�X
const char TITLE_STARTIMG_PAHT[] = { "data/Title/�Q�[���X�^�[�g.png" };		//�X�^�[�g�摜�p�X
const char TITLE_FINIMG_PAHT[] = { "data/Title/4442m.png" };		//�Q�[���I���摜�p�X
const char TITLE_IMG_PATH[] = { "data/Title/TitleName.png" };			//�^�C�g���摜�p�X

struct SBackImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct SStartImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct SFinImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

struct STitleImg
{
	VECTOR m_vPos;
	VECTOR m_Size;
	VECTOR m_Scale;
	int m_iHndl;
};

class CTitle
{
private:
	enum tagTITLE_SCENE {
		TITLE_SCENE_INIT,
		TITLE_SCENE_LOAD,
		TITLE_SCENE_LOOP,
		TITLE_SCENE_END,

		TITLE_SCENE_NUM
	};

	tagTITLE_SCENE m_eSceneID;				//�V�[���ۑ�

	SBackImg m_sBackImg;		//�w�i�摜�̍\����
	STitleImg m_sTitleImg;	//�^�C�g���摜�̍\����
	SStartImg m_sStartImg;	//�X�^�[�g�摜�̍\����
	SFinImg m_sFinImg;		//�I���摜�̍\����

	int MousePosX;		//�}�E�X��X���W
	int MousePosY;		//�}�E�X��Y���W

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTitle();
	~CTitle();


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
