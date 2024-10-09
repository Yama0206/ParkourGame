#include "DebugManager.h"

CDebugManager* CDebugManager::m_Instance = NULL;

//��`
const extern int DEBUG_SPACE = 32;
const extern int DEFAULT_DEBUG_COLOR = 0;

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

