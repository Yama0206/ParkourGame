#include "Object.h"

//定義


void CObject::Init()
{
	
}

void CObject::Load(int iMdHndl)
{
	if (m_iHndl == -1) {
		m_iHndl = MV1DuplicateModel(iMdHndl);
	}
}

void CObject::Step() 
{
	//生存フラグがOFFの時中の処理をしない
	if (!m_IsAllive) return;



}

void CObject::Draw()
{
	//生存フラグがOFFの時中の処理をしない
	if (!m_IsAllive) return;

	//描画処理
	MV1DrawModel(m_iHndl);

}

void CObject::Update()
{
	MV1SetScale(m_iHndl, m_vScale);
	MV1SetPosition(m_iHndl, m_vPos);
}

//情報の設定
void CObject::SetInfo(VECTOR vPos, VECTOR vScale, VECTOR vRot)
{
	m_vPos = vPos;
	m_vRot = vRot;
	m_vSize = vScale;
}