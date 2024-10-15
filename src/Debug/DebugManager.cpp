#include "DebugManager.h"

CDebugManager* CDebugManager::m_Instance = NULL;

//定義
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

void CDebugManager::AddDebugInfo(string DebugString, unsigned int Color, int RowNumber, int ColumnNumber)
{
	Debug debug;
	debug.m_String = DebugString;
	debug.m_Color = Color;

	m_String.push_back(debug);
}

void CDebugManager::AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum, unsigned int Color)
{
	DebugShere sphere;
	sphere.m_vPos = vPos;
	sphere.m_fRad = fRad;
	sphere.m_DivNum = DivNum;
	sphere.m_Color = Color;

	m_Sphere.push_back(sphere);
}

void CDebugManager::Draw()
{
	//デバッグする文字がなかったら処理を行わない
	if (m_String.size() <= 0) return;

	/*for (int i = 0; i < m_String.size(); i++)
	{
		
	}*/

	//球描画
	DrawSphere();
}

void CDebugManager::DrawSphere()
{
	//デバッグする球がなかったら処理を行わない
	if (m_Sphere.size() <= 0) return;

	for (int i = 0; i < m_Sphere.size(); ++i)
	{
		DrawSphere3D(m_Sphere[i].m_vPos, m_Sphere[i].m_fRad, m_Sphere[i].m_DivNum, m_Sphere[i].m_Color, m_Sphere[i].m_Color, false);
	}
}
