#pragma once

#include "Play/ScenePlay.h"
#include "Title/Title.h"
#include "Result/Result.h"
#include "Clear/Clear.h"

class SceneManager
{
private:
	enum tagSCENE {
		SCENE_TITLE,	//タイトル画面
		SCENE_PLAY,		//ゲーム中
		SCENE_RESULT,	//リザルト画面
		SCENE_CLEAR,	//クリア画面

		SCENE_NUM
	};

	CPlayScene cPlayScene;		//プレイシーン
	CTitle	   cTitle;			//タイトルシーン
	CResult    cResult;			//リザルトシーン
	CClear     cClear;
	tagSCENE m_eSceneID;		//シーン保存

public:
	//コンストラクタ
	SceneManager();

	//繰り返し行う処理
	void Loop();

	//描画処理
	void Draw();
};

