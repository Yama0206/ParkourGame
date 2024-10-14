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
		string	m_String;					//�\������f�o�b�O����
		int		m_Color;					//�����̐F
		int		m_RowNumber;				//�`�悷��s�̔ԍ�	
		int		m_ColumnNumber;				//�`�悷���̔ԍ�
	};

	struct DebugShere
	{
		VECTOR	m_vPos;						//���W
		float	m_fRad;						//���a

		int		m_Color;					//�����̐F
	};

	vector <Debug> m_Debug;

public:
	//�V���O���g���̃N���X�擾�ƍ폜--------------
	//CCheckPointManager���擾
	static CDebugManager* GetInstance();
	//CCheckPointManager���폜
	static void DeleteInstance();
	//--------------------------------------------

public:
	void AddDebugInfo(string DebugString, int Color, int RowNumber, int ColumnNumber);

	void AddDebugSphereInfo();

	void Draw();
};
