#include "Clear.h"

CClear::CClear()
{
	m_eSceneID = CLEAR_SCENE_INIT;
	m_vPos = { 0.0f, 0.0f ,0.0f };		//座標
	m_ImgHndl = -1;						//画像ハンドル
}

CClear::~CClear() {}


void CClear::Init()
{
	m_vPos = { 0.0f, 0.0f ,0.0f };
	m_ImgHndl = -1;
}

void CClear::Load()
{
	m_ImgHndl = LoadGraph(CLEAR_IMG_PATH);
}

int CClear::Loop()
{
	int iRet = 0;
	switch (m_eSceneID)
	{
	case CClear::CLEAR_SCENE_INIT:
		Init();
		m_eSceneID = CLEAR_SCENE_LOAD;
		break;
	case CClear::CLEAR_SCENE_LOAD:
		Load();
		m_eSceneID = CLEAR_SCENE_LOOP;
		break;
	case CClear::CLEAR_SCENE_LOOP:
		Step();
		Draw();
		break;
	case CClear::CLEAR_SCENE_END:
		Fin();
		m_eSceneID = CLEAR_SCENE_INIT;
		iRet = 1;
		break;
	}

	return iRet;
}

void CClear::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		m_eSceneID = CLEAR_SCENE_END;
	}
}

void CClear::Draw()
{
	DrawFormatString(32, 32, GetColor(255, 0, 0), "クリア");

	DrawGraph(0, 0, m_ImgHndl, true);
}

void CClear::Fin()
{
	DeleteGraph(m_ImgHndl);
}

