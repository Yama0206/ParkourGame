#pragma once
#include "FootBox.h"
#include "DxLib.h"

//��`
const float ROCK_X_SIZE = 140.0f;
const float ROCK_Y_SIZE = 5.0f;
const float ROCK_Z_SIZE = 120.0f;

class CRock : public CFootBox
{
private:

public:
	void Init();					//������
	void Init(VECTOR vPos, VECTOR vScale);			//�������W
	void Load();					//�ǂݍ���	
	void Step();					//�ʏ폈��
	void Draw();					//�`��
	void Fin();						//�I������
};
