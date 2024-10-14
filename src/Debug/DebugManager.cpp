#include "DebugManager.h"

CDebugManager* CDebugManager::m_Instance = NULL;

//定義
const	  int DEFAULT_DEBUG_COLOR = GetColor(255,0,0);
constexpr int DEFAULT_X_SIZE = 100;
constexpr int DEFAULT_Y_SIZE = 32;
constexpr int DEFAULT_LINENUM = 0;


CDebugManager* CDebugManager::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CDebugManager;
	}

	return m_Instance;
}

void CDebugManager::DeleteInstance()
{
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}

void CDebugManager::AddDebugInfo(string DebugString, int Color, int RowNumber, int ColumnNumber)
{
	Debug debug;
	debug.m_String = DebugString;
	debug.m_Color = Color;
	debug.m_RowNumber = RowNumber;
	debug.m_ColumnNumber = ColumnNumber;

	m_Debug.push_back(debug);
}

void CDebugManager::Draw()
{
	//デバッグする文字がなかったら処理を行わない
	if (m_Debug.size() <= 0) return;

	for (int i = 0; i < m_Debug.size(); i++)
	{
		
	}
}

void CDebugManager::AddDebugSphereInfo()
{

}