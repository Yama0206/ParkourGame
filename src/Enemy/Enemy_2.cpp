#include "Enemy_2.h"

//���t���[���Ăԏ���
void CEnemy_2::Step()
{
	if (!m_IsActive) return;

	//���W�ɑ��x�����Z
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//���͈͂𒴂��������
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_IsActive = false;
	}

	//���W�X�V
	MV1SetPosition(m_iHndl, m_vPos);
}

void CEnemy_2::Shot(CShotManager& cShotManager)
{
	FrameCnt++;

	//�v���C���[�̑̂���o��悤�ɍ��W���グ��
	VECTOR vPos = m_vPos;
	vPos.y += 5.0f;
	//���x�̓v���C���[�Ɠ������@�ňړ����������߂�
	VECTOR vSpd;
	const float SHOT_SPEED = 5.0f;
	vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
	vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
	vSpd.y = 0.0f;
	if (FrameCnt % 60 == 0) {
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}