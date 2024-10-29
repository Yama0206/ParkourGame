#include "DebugManager.h"

CDebugManager* CDebugManager::m_Instance = NULL;

//��`
constexpr int DEFAULT_X_SIZE = 10;
constexpr int DEFAULT_Y_SIZE = 20;
constexpr int DEFAULT_LINENUM = 0;

using namespace std;

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
	//NULL�łȂ��Ȃ�폜
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//�폜������NULL���
	}
}

void CDebugManager::AddDebugInfo(string DebugString, unsigned int Color, int DrawNum)
{
	Debug debug;
	debug.m_String += DebugString;
	debug.m_Color = Color;

	if (DrawNum == -1)
	{
		DrawNum = m_DebugString.size();
	}
	else {
		debug.m_DrawNum = DrawNum;
	}

	m_DebugString.push_back(debug);
}

void CDebugManager::AddDebugNumInfo(int Number, unsigned int Color)
{
	DebugNum debug;
	debug.m_iNum = Number;

	m_DebugNum.push_back(debug);
}

void CDebugManager::AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum, unsigned int Color)
{
	DebugShere debug;
	debug.m_vPos = vPos;
	debug.m_fRad = fRad;
	debug.m_DivNum = DivNum;
	debug.m_Color = Color;

	m_DebugSphere.push_back(debug);
}

void CDebugManager::Step()
{

}

void CDebugManager::Draw()
{
	//�f�o�b�O���镶�����Ȃ������珈�����s��Ȃ�
	if (m_DebugString.size() <= 0 && m_DebugSphere.size() <= 0) return;

	for (int i = 0; i < m_DebugString.size(); i++)
	{
		//�����`��
		DrawFormatString(DEFAULT_X_SIZE, i * DEFAULT_Y_SIZE, m_DebugString[i].m_Color,"%s" ,m_DebugString[i].m_String.c_str());
	}

	//�����`��
	DrawNum();

	//���`��
	DrawSphere();
}

void CDebugManager::DrawNum()
{
	/*if (m_DebugNum.size() <= 0) return;*/

	for (int i = 0; i < m_DebugNum.size(); i++)
	{
		DrawFormatString(10, i * 20, m_DebugNum[i].m_Color, "%d", m_DebugNum[i].m_iNum);
		
	}
	DrawFormatString(500, 100, GetColor(255,0,0), "%d", Num);
	DrawFormatString(500, 120, GetColor(255,0,0), "%d", Num_2);
}

void CDebugManager::DrawSphere()
{
	for (int i = 0; i < m_DebugSphere.size(); ++i)
	{
		DrawSphere3D(m_DebugSphere[i].m_vPos, m_DebugSphere[i].m_fRad, m_DebugSphere[i].m_DivNum, m_DebugSphere[i].m_Color, m_DebugSphere[i].m_Color, false);
	}
}
