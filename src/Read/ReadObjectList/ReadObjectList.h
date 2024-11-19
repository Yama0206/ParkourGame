#pragma once
#include "../Read.h"


using namespace std;

//��`
const char OBJECT_TXT_PATH[] = { "data/File/Object/Object.txt" };

struct SObject
{
	VECTOR m_vPos;		//���W
	VECTOR m_vSize;		//�g�k��
	VECTOR m_vRot;		//��]�l

	ReadType m_eType;		//���
};

class CObjectRead : public CRead
{
private:
	//�I�u�W�F�N�g�����i�[����\����
	SObject m_sObject;

public:
	//�ǂݍ��݃f�[�^���X�g
	vector<SObject> objectInfoList;

	void ReadFile();
};
