#include "BackGround.h"

//‰Šú‰»
void BackGround::Init()
{
	m_vPos = VGet(0.0f, 0.0f, 0.0f);
	m_vScale = { BACKGROUND_X_SCALE, BACKGROUND_Y_SCALE, BACKGROUND_Z_SCALE };
	m_vSize = { BACKGROUND_X_SIZE, BACKGROUND_Y_SIZE, BACKGROUND_Z_SIZE };

	m_ImgHndl = -1;						//‰æ‘œƒnƒ“ƒhƒ‹
}

//“Ç‚İ‚İ
void BackGround::Load()
{
	m_ImgHndl = MV1LoadModel(BACKGROUND_PATH);
}

//’Êíˆ—
void BackGround::Step() {}

//•`‰æˆ—
void BackGround::Draw()
{
	MV1SetScale(m_ImgHndl, m_vScale);
	MV1DrawModel(m_ImgHndl);
}

void BackGround::UpDate()
{
	MV1SetPosition(m_ImgHndl, m_vPos);
}

//I—¹ˆ—
void BackGround::Fin()
{
	MV1DeleteModel(m_ImgHndl);
}
