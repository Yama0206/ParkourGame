#pragma once
#include "DxLib.h"
#include "../Object/Object.h"
#include "../Read/ObjectList/ObjectList.h"

class CObjectManager
{
private:
	//�I�u�W�F�N�g��������Ƃ����̃N���X��������
	

	//�I�u�W�F�N�g����ǂݍ��ނ��߂̃N���X


	//�I�u�W�F�N�g��񂪓����Ă���\����

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

};