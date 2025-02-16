#include "Object.h"

//定義



CObject::CObject() {
	m_iHndl = -1;				//画像ハンドル
}

void CObject::Init()
{
	memset(&m_vPos, 0.0f, sizeof(VECTOR));			//座標
	memset(&m_vRot, 0.0f, sizeof(VECTOR));			//回転値
	memset(&m_vScale, 0.0f, sizeof(VECTOR));		//拡縮率
	memset(&m_vSize, 0.0f, sizeof(VECTOR));			//縦　横　奥行きのサイズ
	m_iHndl = -1;									//画像ハンドル
	m_IsAllive = -1;								//生存フラグ
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
