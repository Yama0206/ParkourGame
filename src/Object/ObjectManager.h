#pragma once
#include "DxLib.h"
#include "../Object/Object.h"

#include "../Read/ReadObjectList/ReadObjectList.h"


const int OBJECT_NUM = 50;

class CObjectManager
{
private:
	//�I�u�W�F�N�g��������Ƃ����̃N���X��������
	CObject m_cObject[OBJECT_NUM];

	//�I�u�W�F�N�g����ǂݍ��ނ��߂̃N���X
	CObjectRead m_cObjectRead;

public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObjectManager();
	~CObjectManager();

	//������
	void Init();
	//�����l�ݒ�
	void InitValue();
	//�f�[�^���[�h
	void Load();
	//�I������
	void Fin();
	//�J��Ԃ��s������
	void Step();
	//�`�揈��
	void Draw();
	//�X�V����
	void Update();

};