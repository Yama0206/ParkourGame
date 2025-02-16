#include "ParkourObject.h"


void CParkourObject::Load(int iModelHndl)
{
	//生存フラグがOFFの時は中の処理をしない
	if (!m_IsAllive) return;

	//複数読み込むようにMV1DuplicateModelを使う
	m_iHndl = MV1DuplicateModel(iModelHndl);
}

void CParkourObject::SetInfo(VECTOR vObjectPos, VECTOR vFrontPos, VECTOR vBackPos, VECTOR vRightPos, VECTOR vLeftPos, bool bIsAllive)
{
	m_vPos = vObjectPos;
	m_vFrontPos = vFrontPos;
	m_vBackPos  = vBackPos;
	m_vRightPos = vRightPos;
	m_vLeftPos  = vLeftPos;

	m_IsAllive = bIsAllive;
}

void CParkourObject::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}