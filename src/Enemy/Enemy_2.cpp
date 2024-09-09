#include "Enemy_2.h"

//毎フレーム呼ぶ処理
void CEnemy_2::Step()
{
	if (!m_IsActive) return;

	//座標に速度を加算
	m_vPos = VAdd(m_vPos, m_vSpeed);
	//一定範囲を超えたら消す
	float fLength = 300.0f;
	if (m_vPos.x > fLength || m_vPos.z < -fLength
		|| m_vPos.z > fLength || m_vPos.z < -fLength)
	{
		m_IsActive = false;
	}

	//座標更新
	MV1SetPosition(m_iHndl, m_vPos);
}

void CEnemy_2::Shot(CShotManager& cShotManager)
{
	FrameCnt++;

	//プレイヤーの体から出るように座標を上げる
	VECTOR vPos = m_vPos;
	vPos.y += 5.0f;
	//速度はプレイヤーと同じ方法で移動方向を決める
	VECTOR vSpd;
	const float SHOT_SPEED = 5.0f;
	vSpd.x = sinf(m_vRot.y) * -SHOT_SPEED;
	vSpd.z = cosf(m_vRot.y) * -SHOT_SPEED;
	vSpd.y = 0.0f;
	if (FrameCnt % 60 == 0) {
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}