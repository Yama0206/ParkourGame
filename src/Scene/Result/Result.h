#pragma once

#include "DxLib.h"
#include "../../Input/Input.h"

const char RESULT_IMG_PATH[] = { "" };

class CResult
{
private:
	enum tagRESULT_SCENE {
		RESULT_SCENE_INIT,
		RESULT_SCENE_LOAD,
		RESULT_SCENE_LOOP,
		RESULT_SCENE_END,

		RESULT_SCENE_NUM
	};

	tagRESULT_SCENE m_eSceneID;				//シーン保存

	VECTOR m_vPos;
	int m_ImgHndl;

public:
	//コンストラクタ・デストラクタ
	CResult();
	~CResult();


	//繰り返し行う処理
	int Loop();
	//描画処理
	void Draw();

private:
	//初期化
	void Init();
	//終了処理
	void Fin();
	//データロード
	void Load();
	//毎フレーム
	void Step();
};

