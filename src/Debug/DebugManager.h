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
#define DEFALUT_COLOR  GetColor(255,255,255)
const unsigned int DEFAULT_DEBUG_COLOR = GetColor(255, 0, 0);
const unsigned int DEFALUT_SPHERE_COLOR = GetColor(171, 225, 250);

constexpr int DEFALUT_DIV_NUM = 16;

//デバッグ文言表示リストのサイズ
constexpr int TEXTINFO_LIST_SIZE = 50;

//表示文字列のサイズ
constexpr int CHAR_SIZE = 512;

//デバッグ文言表示用構造体
struct  TextInfo
{
	int m_x;					// X座標
	int m_y;					// Y座標
	string DebugString;			// 文言
	unsigned int Color;			// 文字色
	bool IsUse;					// 使用フラグ
};

struct  BoxInfo
{
	VECTOR m_vPos;
	VECTOR m_vSize;
};

class CDebugManager
{
private:
	static CDebugManager* m_Instance;

private:


	struct DebugShere
	{
		VECTOR			m_vPos;						//座標
		float			m_fRad;						//半径
		int				m_DivNum;					//球を形成するポリゴンの細かさ
		unsigned int	m_Color;					//球の色
	};

	vector <DebugShere>	 m_DebugSphere;					//デバッグ球

	int Num;
	int Num_2;

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

	//出力ログに表示
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	//球
	void AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum = DEFALUT_DIV_NUM, unsigned int Color = DEFALUT_SPHERE_COLOR);

public:
	//描画(球)
	void DrawSphere();
	//描画
	void Draw();

private:
	//デバッグ文言の表示リスト
	list<TextInfo> m_TextInfoList;

	//listにデータを追加
	void AddTextInfo(TextInfo _textInfo);
};
