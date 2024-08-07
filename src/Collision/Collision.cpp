
#include "Collision.h"

//2D
//IsHitRect�̒�`
bool IsHitRect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
	if (Bx < Ax + Aw &&
		Bx + Bw > Ax &&
		By + Bh > Ay &&
		By < Ay + Ah)
	{
		// �������Ă���Ƃ��̏���
		return true;
	}
	return false;
}

//IsHitCircle�̒�`
bool IsHitCircle(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY)) {
		//�������Ă��鎞�̏���
		return true;
	}

	return false;

}

//3D
//�����̓����蔻��
bool IsHitRect(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
	if (bPos.x < aPos.x + aSize.x &&
		bPos.x + bSize.x > aPos.x &&
		bPos.y + bSize.y > aPos.y &&
		bPos.y < aPos.y + aSize.y &&
		bPos.z + bSize.z > aPos.z &&
		bPos.z < aPos.z + aSize.z)
	{
		//�������Ă��鎞�̏���
		return true;
	}

	//�������Ă��Ȃ��Ƃ�
	return false;
}

//���̓����蔻��
bool SphereCollision(float aR, VECTOR aPos, float bR, VECTOR bPos)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) +
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - aPos.z) * (aPos.z - aPos.z))
	{
		//�������Ă���Ƃ�
		return true;
	}
	//�������Ă��Ȃ��Ƃ�
	return false;
}