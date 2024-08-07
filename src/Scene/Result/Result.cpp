#include "Result.h"

CResult::CResult()
{
	m_eSceneID = RESULT_SCENE_INIT;
	m_vPos = { 0.0f, 0.0f ,0.0f };		//座標
	m_ImgHndl = -1;						//画像ハンドル
}

CResult::~CResult() {}


void CResult::Init()
{
	m_vPos = { 0.0f, 0.0f ,0.0f };
	m_ImgHndl = -1;
}

void CResult::Load()
{
	m_ImgHndl = LoadGraph(RESULT_IMG_PATH);
}

int CResult::Loop()
{
	int iRet = 0;
	switch (m_eSceneID)
	{
	case CResult::RESULT_SCENE_INIT:
		Init();
		m_eSceneID = RESULT_SCENE_LOAD;
		break;
	case CResult::RESULT_SCENE_LOAD:
		Load();
		m_eSceneID = RESULT_SCENE_LOOP;
		break;
	case CResult::RESULT_SCENE_LOOP:
		Step();
		Draw();
		break;
	case CResult::RESULT_SCENE_END:
		Fin();
		m_eSceneID = RESULT_SCENE_INIT;
		iRet = 1;
		break;
	}

	return iRet;
}

void CResult::Step()
{
	if (CInput::IsKeyPush(KEY_INPUT_RETURN))
	{
		m_eSceneID = RESULT_SCENE_END;
	}
}

void CResult::Draw()
{
	DrawFormatString(32, 32, GetColor(255, 0, 0), "リザルト");

	DrawGraph(0, 0, m_ImgHndl, true);
}

void CResult::Fin()
{
	DeleteGraph(m_ImgHndl);
}
