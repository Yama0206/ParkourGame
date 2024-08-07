#pragma once
#include "DxLib.h"
#include "../../Input/Input.h"

const char CLEAR_IMG_PATH[] = { "" };

class CClear {
private:
	enum tagCLEAR_SCENE {
		CLEAR_SCENE_INIT,
		CLEAR_SCENE_LOAD,
		CLEAR_SCENE_LOOP,
		CLEAR_SCENE_END,

		CLEAR_SCENE_NUM
	};

	tagCLEAR_SCENE m_eSceneID;				//シーン保存

	VECTOR m_vPos;
	int m_ImgHndl;

public:
	//コンストラクタ・デストラクタ
	CClear();
	~CClear();


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
