#pragma once
#include "../ParkourObject.h"
#include <vector>

using namespace std;

class ParkourObjectManager
{
private:
	enum {

	};

public:
	// 初期化
	void Init();
	// 読み込み
	void Load();
	// 描画処理
	void Draw();
	// 更新処理
	void Update();

public:
	//コンストラクタ
	ParkourObjectManager();
	//デストラクタ
	~ParkourObjectManager();

public:

};
