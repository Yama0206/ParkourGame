#pragma once]
#include "DxLib.h"
#include <vector>
#include <algorithm>
#include "string"

using namespace std;

//定義
const unsigned int DEFAULT_DEBUG_COLOR = GetColor(255, 0, 0);
const unsigned int DEFALUT_SPHERE_COLOR = GetColor(171, 225, 250);
constexpr int DEFALUT_DIV_NUM = 8;

class CDebugManager
{
private:
	static CDebugManager* m_Instance;

private:
	struct Debug
	{
		string			m_String;					//表示するデバッグ文字
		unsigned int	m_Color;					//文字の色
		int				m_DrawNum;					//表示番号
	};

	struct DebugShere
	{
		VECTOR			m_vPos;						//座標
		float			m_fRad;						//半径
		int				m_DivNum;					//球を形成するポリゴンの細かさ
		unsigned int	m_Color;					//球の色
	};

	vector <Debug>		 m_DebugString;					//デバッグ文字
	vector <DebugShere>	 m_DebugSphere;					//デバッグ球

public:
	//シングルトンのクラス取得と削除--------------
	//CCheckPointManagerを取得
	static CDebugManager* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();
	//--------------------------------------------

public:
	void AddDebugInfo(string DebugString, unsigned int Color = DEFAULT_DEBUG_COLOR, int DrawNum = -1);

	void AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum = DEFALUT_DIV_NUM, unsigned int Color = DEFALUT_SPHERE_COLOR);

	void Step();

	void DrawSphere();

	void Draw();
};
