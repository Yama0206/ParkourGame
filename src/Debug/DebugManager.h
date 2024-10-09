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
	//CCheckPointManager‚ğæ“¾
	static CDebugManager* GetInstance();

	//CCheckPointManager‚ğíœ
	static void DeleteInstance();

public:


};
