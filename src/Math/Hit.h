#pragma once
#include "DxLib.h"
#include "../Collision/Collision.h"

static class CHit
{
public:
	//2D�֐�

	//�_�Ƌ�`�̓����蔻��
	//vDotPos		:	�_�̈ʒu
	//vSquarePos	:	��`�̒��S�ʒu
	//vSize			:	��`�̏c�A����(���a)


//2D�̓����蔻��
//�l�p�`�̓����蔻��
//IsHitRect�̃v���g�^�C�v�錾
	static bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
	//3D�̓����蔻��
	//������,�I�u�W�F�N�g1�̍��W�A������,�I�u�W�F�N�g1�̕��E�����E���s��
	//��O����,�I�u�W�F�N�g2�̍��W�A��l����,�I�u�W�F�N�g2�̕��E�����E���s��
	static bool IsHitRect(VECTOR ACenterPos, VECTOR AHalfSize, VECTOR BCenterPos, VECTOR BHalfSize);


	//�~�̓����蔻��
	//IsHitCircle�̃v���g�^�C�v�錾
	static bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR);
	//���̓����蔻��
	//�������A��1�̔��a�A�������A��1�̍��W
	//��O�����A��2�̔��a�A��l�����A��2�̍��W
	static bool IsHiSphere( VECTOR aPos, float aR, VECTOR bPos, float bR);
};
