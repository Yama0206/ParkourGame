#pragma once

//�x�N�g���̉��Z
VECTOR AddVec(VECTOR _vec1, VECTOR _vec2);
VECTOR AddVec(VECTOR _vec1, float x = 0.0f, float y = 0.0f, float z = 0.0f);

//�x�N�g���̌��Z
VECTOR SubVec(VECTOR _vec1, VECTOR _vec2);

//�x�N�g���̐���
VECTOR VecCreate(VECTOR _start, VECTOR _end);

//�x�N�g���̒������v�Z
float LongVec(VECTOR _vec);

//�x�N�g���𐳋K������
VECTOR NormalizeVec(VECTOR _vec);

//�x�N�g�����X�J���[�{����֐�
VECTOR ScaleVec(VECTOR _vec, float scale);

//�x�N�g�������Z����֐�
VECTOR DivVec(VECTOR _vec, float div);

//����
float VecDot(VECTOR vec1, VECTOR vec2);

//�O��
float VecCross2D(VECTOR vec1, VECTOR vec2);

//�p�x�ϊ�
float TransAngleToRadian(float Angle);

//�x�N�^�[�̐�Βl��Ԃ�
VECTOR Vabs(VECTOR vNum);

//2�_�Ԃ̋����Ɛ��K��
//2D
//��1����, 1�ڂ�X���W  ��2����, 1�ڂ�Y���W
//��3����, 2�ڂ�X���W  ��4����, 2�ڂ�Y���W
float VecTwoPoint2D(float x_1, float y_1, float x_2, float y_2);
//3D
//��1����, 1�ڂ̍��W�@�@��2����, 2�ڂ̍��W
float VecTwoPoint3D(VECTOR vec1, VECTOR vec2);
