#pragma once]
#include "DxLib.h"
#include <vector>
#include <list>
#include <algorithm>
#include "string"

using namespace std;

//定義
//デバッグフラグ
constexpr bool IsDeBug = true;

//デバッグ文言の色
#define DEFAULT_COLOR			 GetColor(255,255,255)
#define DEFAULT_DEBUG_COLOR		 GetColor(255, 0, 0)
#define DEFAULT_SPHERE_COLOR	 GetColor(171, 225, 250)
#define DEFAULT_UP_BOX_COLOR	 GetColor(255,0,0)
#define DEFAULT_DOWN_BOX_COLOR	 GetColor(0,0,255)
#define DEFAULT_SIDE_BOX_COLOR	 GetColor(0,255,0)

constexpr int DEFAULT_DIV_NUM = 16;

//デバッグ文言表示リストのサイズ
constexpr int TEXTINFO_LIST_SIZE = 50;

//表示文字列のサイズ
constexpr int CHAR_SIZE = 512;

//デバッグボックスのサイズ
constexpr int BOX_LIST_SIZE = 50;

//デバッグ球のサイズ
constexpr int SPHERE_LIST_SIZE = 50;

//デバッグ文言表示用構造体
struct  TextInfo
{
	int m_x;					// X座標
	int m_y;					// Y座標
	string DebugString;			// 文言
	unsigned int Color;			// 文字色
	bool IsUse;					// 使用フラグ
};

//デバッグボックス
struct  BoxInfo
{
	VECTOR m_vPos;				// 座標
	VECTOR m_vSize;				// サイズ
	unsigned int ColorUp;		// 色
	unsigned int ColorDown;		// 色
	unsigned int ColorSide;		// 色
	bool IsUse;					// 使用フラグ
};

//デバッグ球
struct SphereInfo
{
	VECTOR			m_vPos;		// 座標
	float			m_fRad;		// 半径
	int				m_DivNum;	// 球を形成するポリゴンの細かさ
	unsigned int	m_Color;	// 球の色
	bool			IsUse;		// 使用フラグ
};

class CDebugManager
{
private:
	//インスタンス
	static CDebugManager* m_Instance;

private:
	//メンバ変数
	//デバッグ文言の表示リスト
	list<TextInfo>		m_TextInfoList;
	//デバッグ球表示リスト
	vector <SphereInfo>	m_DebugSphereList;
	//デバッグボックス表示リスト
	vector <BoxInfo>	m_DebugBoxList;

public:
	//シングルトンのクラス取得と削除--------------
	//CCheckPointManagerを取得
	static CDebugManager* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();
	//--------------------------------------------

public:
	CDebugManager();
	~CDebugManager();

public:
	//デバッグ文言データを追加
	void AddString(int _x, int _y, string _string);
	void AddFormatString(int _x, int _y, const char* format, ...);
	//デバッグボックスデータを追加
	void AddBox(VECTOR vPos, VECTOR vSize, unsigned int ColorUp = DEFAULT_UP_BOX_COLOR, unsigned int ColorDown = DEFAULT_DOWN_BOX_COLOR, unsigned int ColorSide = DEFAULT_SIDE_BOX_COLOR);
	//球
	void AddSphere(VECTOR vPos, float fRad, int DivNum = DEFAULT_DIV_NUM, unsigned int Color = DEFAULT_SPHERE_COLOR);

	//出力ログに表示
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	//箱
	void DrawBox3D(VECTOR Pos, VECTOR Size, unsigned int ColorUp, unsigned int ColorDown, unsigned int ColorSide);

public:
	//描画(球)
	void DrawSphere();
	//描画
	void Draw();

private:
	//listにデータを追加
	void AddTextInfo(TextInfo _textInfo);

	//ボックスをデータ追加
	void AddBoxInfo(BoxInfo _boxInfo);

	//球のデータを追加
	void AddSphereInfo(SphereInfo _sphereInfo);
};
