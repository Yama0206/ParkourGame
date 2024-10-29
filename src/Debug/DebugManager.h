#pragma once]
#include "DxLib.h"
#include <vector>
#include <algorithm>
#include "string"

using namespace std;

//��`
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
		string			m_String;					//�\������f�o�b�O����
		unsigned int	m_Color;					//�����̐F
		int				m_DrawNum;					//�\���ԍ�
	};

	struct DebugNum
	{
		VECTOR			m_vPos;						//���W
		int				m_iNum;						//�f�o�b�O���鐔��
		unsigned int	m_Color;					//�����̐F
	};

	struct DebugShere
	{
		VECTOR			m_vPos;						//���W
		float			m_fRad;						//���a
		int				m_DivNum;					//�����`������|���S���ׂ̍���
		unsigned int	m_Color;					//���̐F
	};

	vector <Debug>		 m_DebugString;					//�f�o�b�O����
	vector <DebugNum>	 m_DebugNum;					//�f�o�b�O����
	vector <DebugShere>	 m_DebugSphere;					//�f�o�b�O��

	int Num;
	int Num_2;

public:
	//�V���O���g���̃N���X�擾�ƍ폜--------------
	//CCheckPointManager���擾
	static CDebugManager* GetInstance();
	//CCheckPointManager���폜
	static void DeleteInstance();
	//--------------------------------------------

public:
	//����
	void AddDebugInfo(string DebugString, unsigned int Color = DEFAULT_DEBUG_COLOR, int DrawNum = -1);
	//����
	void AddDebugNumInfo(int DebugNum, unsigned int Color = DEFAULT_DEBUG_COLOR);
	//��
	void AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum = DEFALUT_DIV_NUM, unsigned int Color = DEFALUT_SPHERE_COLOR);
	//�ʏ폈��
	void Step();
	//�`��(��)
	void DrawSphere();
	//�`��(����)
	void DrawNum();
	//�`��
	void Draw();

	void SetNum(int num) { Num = num; }
	void SetNum_2(int num) { Num_2 = num; }
};
