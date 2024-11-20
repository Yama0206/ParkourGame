#include "DxLib.h"
#include "Math.h"
#include <math.h>

//�x�N�g�������Z
VECTOR AddVec(VECTOR _vec1, VECTOR _vec2)
{
	VECTOR ret;
	ret.x = _vec1.x + _vec2.x;
	ret.y = _vec1.y + _vec2.y;
	ret.z = _vec1.z + _vec2.z;

	return ret;
}

VECTOR AddVec(VECTOR _vec1, float x, float y, float z)
{
	VECTOR ret;
	ret.x = _vec1.x + x;
	ret.y = _vec1.y + y;
	ret.z = _vec1.z + z;

	return ret;
}

//�x�N�g�������Z
VECTOR SubVec(VECTOR _vec1, VECTOR _vec2)
{
	VECTOR ret;
	ret.x = _vec1.x - _vec2.x;
	ret.y = _vec1.y - _vec2.y;
	ret.z = _vec1.z - _vec2.z;

	return ret;
}

//�x�N�g���𐶐�����
VECTOR VecCreate(VECTOR _start, VECTOR _end)
{
	VECTOR ret;

	ret.x = _end.x - _start.x;
	ret.y = _end.y - _start.y;
	ret.z = _end.z - _start.z;

	return ret;
}

//�x�N�g���̒������v�Z
float LongVec(VECTOR _vec)
{
	float c = _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;

	 c = sqrtf(c);

	 return c;
}

//�x�N�g���𐳋K������
VECTOR NormalizeVec(VECTOR _vec)
{
	VECTOR ret = { 0 };

	ret.x = ret.x / LongVec(_vec);
	ret.y = ret.y / LongVec(_vec);
	ret.z = ret.z / LongVec(_vec);

	return ret;
}

//�x�N�g�����X�J���[�{����֐�
VECTOR ScaleVec(VECTOR _vec, float scale)
{
	VECTOR ret;

	ret.x = _vec.x * scale;
	ret.y = _vec.y * scale;
	ret.z = _vec.z * scale;

	return ret;
}
//�x�N�g���̊���Z
VECTOR DivVec(VECTOR _vec, float div)
{
	VECTOR ret;

	ret.x = _vec.x / div;
	ret.y = _vec.y / div;
	ret.z = _vec.z / div;

	return ret;
}

//�x�N�g���̓���
float VecDot(VECTOR vec1, VECTOR vec2)
{
	float c;

	c = vec1.x * vec2.x + vec1.y * vec2.y;

	return c;
}

float VecCross2D(VECTOR vec1, VECTOR vec2)
{
	float c;

	c = vec1.x * vec2.y - vec1.y * vec2.x;

	return c;

}

float VecTwoPoint2D(float x_1, float y_1, float x_2, float y_2)
{
	//�x�N�g��
	VECTOR vPos = { 0.0f, 0.0f , 0.0f };
	
	//��_��
	float TwoPoint = 0.0f;

	//�x�N�g��
	vPos.x = x_1 - x_2;
	vPos.y = y_1 - y_2;

	//2�_�Ԃ̋������擾
	TwoPoint = (vPos.x * vPos.x) + (vPos.y * vPos.y);

	//������
	TwoPoint = sqrtf(TwoPoint);


	return TwoPoint;
}


float VecTwoPoint3D(VECTOR vec1, VECTOR vec2)
{
	VECTOR vPos = { 0.0f, 0.0f , 0.0f };
	float TwoPoint = 0.0f;

	//�x�N�g��
	vPos.x = vec2.x - vec1.x;
	vPos.y = vec2.y - vec1.y;
	vPos.z = vec2.z - vec1.z;

	//2�_�Ԃ̋������擾
	TwoPoint = (vPos.x * vPos.x) + (vPos.y * vPos.y) + (vPos.z * vPos.z);

	//������
	TwoPoint = sqrtf(TwoPoint);

	return TwoPoint;
}

//�p�x���烉�W�A���l�̕ϊ�
float TransAngleToRadian(float Angle)
{
	float Radian;

	Radian = Angle * DX_PI_F / 180;

	return Radian;
}

VECTOR Vabs(VECTOR vNum)
{
	VECTOR vAbsNum;

	vAbsNum.x = fabsf(vNum.x);
	vAbsNum.y = fabsf(vNum.y);
	vAbsNum.z = fabsf(vNum.z);

	return vAbsNum;
}

