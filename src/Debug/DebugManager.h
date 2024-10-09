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
		string m_String;

	};

	vector <Debug> m_Debug;

public:
	//CCheckPointManager���擾
	static CDebugManager* GetInstance();

	//CCheckPointManager���폜
	static void DeleteInstance();

public:


};
