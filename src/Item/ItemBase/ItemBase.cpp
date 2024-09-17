#include "ItemBase.h"

void CItemBase::Load(int iModelHndl)
{
	//生存フラグがOFFの時は中の処理をしない
	if (!m_IsAllive) return;

	//複数読み込むようにMV1DuplicateModelを使う
	m_iHndl = MV1DuplicateModel(iModelHndl);
}


void CItemBase::Draw()
{
	//生存フラグがOFFの時
	if (!m_IsAllive) return;

	MV1DrawModel(m_iHndl);

}

//情報の設定
void CItemBase::SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vScale)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vScale = vScale;
}

void CItemBase::Update()
{
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}