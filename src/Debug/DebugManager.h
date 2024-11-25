#pragma once]
#include "DxLib.h"
#include <vector>
#include <list>
#include <algorithm>
#include "string"

using namespace std;

//��`
//�f�o�b�O�t���O
constexpr bool IsDeBug = true;

//�f�o�b�O�����̐F
#define DEFALUT_COLOR  GetColor(255,255,255)
const unsigned int DEFAULT_DEBUG_COLOR = GetColor(255, 0, 0);
const unsigned int DEFALUT_SPHERE_COLOR = GetColor(171, 225, 250);

constexpr int DEFALUT_DIV_NUM = 16;

//�f�o�b�O�����\�����X�g�̃T�C�Y
constexpr int TEXTINFO_LIST_SIZE = 50;

//�\��������̃T�C�Y
constexpr int CHAR_SIZE = 512;

//�f�o�b�O�����\���p�\����
struct  TextInfo
{
	int m_x;					// X���W
	int m_y;					// Y���W
	string DebugString;			// ����
	unsigned int Color;			// �����F
	bool IsUse;					// �g�p�t���O
};

struct  BoxInfo
{
	VECTOR m_vPos;
	VECTOR m_vSize;
};

class CDebugManager
{
private:
	static CDebugManager* m_Instance;

private:


	struct DebugShere
	{
		VECTOR			m_vPos;						//���W
		float			m_fRad;						//���a
		int				m_DivNum;					//�����`������|���S���ׂ̍���
		unsigned int	m_Color;					//���̐F
	};

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
	CDebugManager();
	~CDebugManager();

public:
	//�f�o�b�O�����f�[�^��ǉ�
	void AddString(int _x, int _y, string _string);
	void AddFormatString(int _x, int _y, const char* format, ...);

	//�o�̓��O�ɕ\��
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	//��
	void AddDebugSphereInfo(VECTOR vPos, float fRad, int DivNum = DEFALUT_DIV_NUM, unsigned int Color = DEFALUT_SPHERE_COLOR);

public:
	//�`��(��)
	void DrawSphere();
	//�`��
	void Draw();

private:
	//�f�o�b�O�����̕\�����X�g
	list<TextInfo> m_TextInfoList;

	//list�Ƀf�[�^��ǉ�
	void AddTextInfo(TextInfo _textInfo);
};
