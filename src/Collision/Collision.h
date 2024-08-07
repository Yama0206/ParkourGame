
#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "DxLib.h"

//2D�̓����蔻��
//�l�p�`�̓����蔻��
//IsHitRect�̃v���g�^�C�v�錾
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
//3D�̓����蔻��
//������,�I�u�W�F�N�g1�̍��W�A������,�I�u�W�F�N�g1�̕��E�����E���s��
//��O����,�I�u�W�F�N�g2�̍��W�A��l����,�I�u�W�F�N�g2�̕��E�����E���s��
bool IsHitRect(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);


//�~�̓����蔻��
//IsHitCircle�̃v���g�^�C�v�錾
bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR);
//���̓����蔻��
//�������A��1�̔��a�A�������A��1�̍��W
//��O�����A��2�̔��a�A��l�����A��2�̍��W
bool SphereCollision(float aR, VECTOR aPos, float bR, VECTOR bPos);

#endif
