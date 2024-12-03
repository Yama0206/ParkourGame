#pragma once
#include "../ParkourObject.h"
#include "../../Read/ReadParkourObjectList/ReadParkourObjectList.h"
#include <vector>

using namespace std;

class CParkourObjectManager
{
private:
	//インスタンス
	static CParkourObjectManager* m_Instance;

private:
	enum Dir {
		FRONT,			//前
		BACK,			//後ろ
		LEFT,			//左
		RIGHT,			//右
	};

	//ベースクラス
	vector<CParkourObject*> m_cParkourObjectList;

	//読み込みリストクラス
	ReadParkourObjectList m_cFileDataList;

public:
	//インスタンス取得
		//CCheckPointManagerを取得
	static CParkourObjectManager* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();

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
	CParkourObjectManager();
	//デストラクタ
	~CParkourObjectManager();

public:
	//アイテムリストクラスを取得
	inline CParkourObject* GetParkourObject(int iID) { return m_cParkourObjectList[iID]; }

	//アイテムリストの数を取得
	int GetParkourObjectSize() { return m_cParkourObjectList.size(); }

};
