#pragma once
#include "../Object/Object.h"


class CJumpObject : public CObject
{
private:
	bool IsHit;			//���������ǂ���
public:
	//�����ݒ�
	void InitValue();
	//�ʏ폈��
	void Step();
};