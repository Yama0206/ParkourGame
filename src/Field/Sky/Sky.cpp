#include "Sky.h"

const float ROT_SPEED = 0.0001;			//回転スピード

void CSky::Init()
{
	m_vPos = { 0.1f, 0.1f, 0.1f };
	m_vScale = { 0.5f, 0.5f, 0.5f };
	m_vRot = { 0.0f, 0.0f, 0.0f };	

	m_ImgHndl = -1;
}

//読み込み
void CSky::Load()
{
	m_ImgHndl = MV1LoadModel(SKY_IMG_PATH);
}

//通常処理
void CSky::Step()
{
	m_vRot.y += ROT_SPEED;
}

//描画処理
void CSky::Draw()
{
	MV1DrawModel(m_ImgHndl);
}

void CSky::UpDate()
{
	MV1SetRotationXYZ(m_ImgHndl, m_vRot);
	MV1SetPosition(m_ImgHndl, m_vPos);
}

//終了処理
void CSky::Fin()
{
	MV1DeleteModel(m_ImgHndl);
}