#pragma once]
#include "DxLib.h"
#include <vector>
#include "string"

using namespace std;

class CDebugManager
{
private:
	static CDebugManager* m_Instance;

private:
	struct Debug
	{
		string	m_String;					//表示するデバッグ文字
		int		m_Color;					//文字の色
		int		m_RowNumber;				//描画する行の番号	
		int		m_ColumnNumber;				//描画する列の番号
	};

	struct DebugShere
	{
		VECTOR	m_vPos;						//座標
		float	m_fRad;						//半径

		int		m_Color;					//文字の色
	};

	vector <Debug> m_Debug;

public:
	//シングルトンのクラス取得と削除--------------
	//CCheckPointManagerを取得
	static CDebugManager* GetInstance();
	//CCheckPointManagerを削除
	static void DeleteInstance();
	//--------------------------------------------

public:
	void AddDebugInfo(string DebugString, int Color, int RowNumber, int ColumnNumber);

	void AddDebugSphereInfo();

	void Draw();
};
