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
#define DEFAULT_COLOR			 GetColor(255,255,255)
#define DEFAULT_DEBUG_COLOR		 GetColor(255, 0, 0)
#define DEFAULT_SPHERE_COLOR	 GetColor(171, 225, 250)
#define DEFAULT_UP_BOX_COLOR	 GetColor(255,0,0)
#define DEFAULT_DOWN_BOX_COLOR	 GetColor(0,0,255)
#define DEFAULT_SIDE_BOX_COLOR	 GetColor(0,255,0)

constexpr int DEFAULT_DIV_NUM = 16;

//�f�o�b�O�����\�����X�g�̃T�C�Y
constexpr int TEXTINFO_LIST_SIZE = 50;

//�\��������̃T�C�Y
constexpr int CHAR_SIZE = 512;

//�f�o�b�O�{�b�N�X�̃T�C�Y
constexpr int BOX_LIST_SIZE = 50;

//�f�o�b�O���̃T�C�Y
constexpr int SPHERE_LIST_SIZE = 50;

//�f�o�b�O�����\���p�\����
struct  TextInfo
{
	int m_x;					// X���W
	int m_y;					// Y���W
	string DebugString;			// ����
	unsigned int Color;			// �����F
	bool IsUse;					// �g�p�t���O
};

//�f�o�b�O�{�b�N�X
struct  BoxInfo
{
	VECTOR m_vPos;				// ���W
	VECTOR m_vSize;				// �T�C�Y
	unsigned int ColorUp;		// �F
	unsigned int ColorDown;		// �F
	unsigned int ColorSide;		// �F
	bool IsUse;					// �g�p�t���O
};

//�f�o�b�O��
struct SphereInfo
{
	VECTOR			m_vPos;		// ���W
	float			m_fRad;		// ���a
	int				m_DivNum;	// �����`������|���S���ׂ̍���
	unsigned int	m_Color;	// ���̐F
	bool			IsUse;		// �g�p�t���O
};

class CDebugManager
{
private:
	//�C���X�^���X
	static CDebugManager* m_Instance;

private:
	//�����o�ϐ�
	//�f�o�b�O�����̕\�����X�g
	list<TextInfo>		m_TextInfoList;
	//�f�o�b�O���\�����X�g
	vector <SphereInfo>	m_DebugSphereList;
	//�f�o�b�O�{�b�N�X�\�����X�g
	vector <BoxInfo>	m_DebugBoxList;

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
	//�f�o�b�O�{�b�N�X�f�[�^��ǉ�
	void AddBox(VECTOR vPos, VECTOR vSize, unsigned int ColorUp = DEFAULT_UP_BOX_COLOR, unsigned int ColorDown = DEFAULT_DOWN_BOX_COLOR, unsigned int ColorSide = DEFAULT_SIDE_BOX_COLOR);
	//��
	void AddSphere(VECTOR vPos, float fRad, int DivNum = DEFAULT_DIV_NUM, unsigned int Color = DEFAULT_SPHERE_COLOR);

	//�o�̓��O�ɕ\��
	void DrawLogString(string _string);
	void DrawLogFormatString(const char* format, ...);
	//��
	void DrawBox3D(VECTOR Pos, VECTOR Size, unsigned int ColorUp, unsigned int ColorDown, unsigned int ColorSide);

public:
	//�`��(��)
	void DrawSphere();
	//�`��
	void Draw();

private:
	//list�Ƀf�[�^��ǉ�
	void AddTextInfo(TextInfo _textInfo);

	//�{�b�N�X���f�[�^�ǉ�
	void AddBoxInfo(BoxInfo _boxInfo);

	//���̃f�[�^��ǉ�
	void AddSphereInfo(SphereInfo _sphereInfo);
};
