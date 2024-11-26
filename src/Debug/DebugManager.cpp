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

//�R���X�g���N�^
CDebugManager::CDebugManager()
{
	//���X�g�̏�����
	m_TextInfoList.resize(TEXTINFO_LIST_SIZE);
	for (TextInfo& value : m_TextInfoList)
	{
		value.IsUse = false;
	}

	m_DebugBoxList.resize(BOX_LIST_SIZE);
	for (BoxInfo& value : m_DebugBoxList)
	{
		value.IsUse = false;
	}

	m_DebugSphereList.resize(SPHERE_LIST_SIZE);
	for (SphereInfo& value : m_DebugSphereList)
	{
		value.IsUse = false;
	}
}

//�f�X�g���N�^
CDebugManager::~CDebugManager()
{

}

void CDebugManager::AddSphere(VECTOR vPos, float fRad, int DivNum, unsigned int Color)
{
	SphereInfo value = { vPos, fRad, DivNum, Color, true};

	AddSphereInfo(value);
}

void CDebugManager::AddString(int _x, int _y, string _string)
{
	TextInfo value = { _x, _y, _string, DEFAULT_COLOR, true };

	AddTextInfo(value);
}

void CDebugManager::AddFormatString(int _x, int _y, const char* format, ...)
{
	//�t�H�[�}�b�g�ςݕ�������i�[����o�b�t�@
	char buffer[CHAR_SIZE];

	//�ψ���������
	va_list args;
	va_start(args, format);
	//�t�H�[�}�b�g�ς݂̕�����𐶐�����
	vsnprintf(buffer, sizeof(buffer), format, args);

	va_end(args);

	TextInfo value = { _x, _y, buffer, DEFAULT_COLOR, true };

	AddTextInfo(value);

}

void CDebugManager::AddBox(VECTOR vPos, VECTOR vSize, unsigned int ColorUp, unsigned int ColorDown, unsigned int ColorSide)
{
	BoxInfo value = { vPos, vSize, ColorUp, ColorDown, ColorSide, true };

	AddBoxInfo(value);
}

void CDebugManager::DrawLogString(string _string)
{
	if (!IsDeBug) { return; }

	_string += "\n";

	OutputDebugString(_string.c_str());
}


void CDebugManager::DrawLogFormatString(const char* format, ...)
{
	//�t�H�[�}�b�g�ςݕ�������i�[����o�b�t�@
	char buffer[CHAR_SIZE];

	//�ψ���������
	va_list args;
	va_start(args, format);
	//�t�H�[�}�b�g�ς݂̕�����𐶐�����
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLogString(buffer);
}

void CDebugManager::Draw()
{
	if (!IsDeBug) { return; }

	//�f�o�b�O����
	for (TextInfo& value : m_TextInfoList)
	{
		if (value.IsUse) {
			DrawString(value.m_x, value.m_y, value.DebugString.c_str(), value.Color);
			//�\�������疢�g�p�ɂ���
			value.IsUse = false;
		}
	}

	//�f�o�b�O�{�b�N�X
	for (BoxInfo& value : m_DebugBoxList)
	{
		if (value.IsUse) {
			DrawBox3D(value.m_vPos, value.m_vSize, value.ColorUp, value.ColorDown, value.ColorSide);
			//�\�������疢�g�p�ɂ���
			value.IsUse = false;
		}
	}

	//�f�o�b�O��
	for (SphereInfo& value : m_DebugSphereList)
	{
		if (value.IsUse) {
			DrawSphere3D(value.m_vPos, value.m_fRad, value.m_DivNum, value.m_Color, value.m_Color, false);
			//�\�������疢�g�p�ɂ���
			value.IsUse = false;
		}
	}
}

void CDebugManager::DrawBox3D(VECTOR Pos, VECTOR Size, unsigned int ColorUp, unsigned int ColorDown, unsigned int ColorSide)
{

	//�T�C�Y�̔������Ƃ�
	VECTOR HalfSize = VScale(Size, 0.5f);

	/*��̖�*/
	//������E(��O)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), ColorUp);
	//������E(��)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);
	//����O���獶��
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);
	//�E��O����E��
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);

	/*���̖�*/
	//������E(��O)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorDown);
	//������E(��)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);
	//����O���獶��
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);
	//�E��O����E��
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);

	/*����*/
	//��O��(�ォ�牺)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorSide);
	//��O�E(�ォ�牺)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorSide);
	//����(�ォ�牺)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorSide);
	//���E(�ォ�牺)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorSide);
}

void CDebugManager::AddTextInfo(TextInfo _textInfo)
{
	for (TextInfo& value : m_TextInfoList)
	{
		if (!value.IsUse) {
			//�f�[�^��ǉ�
			value = _textInfo;
			return;
		}
	}
}

void CDebugManager::AddBoxInfo(BoxInfo _BoxInfo)
{
	for (BoxInfo& value : m_DebugBoxList)
	{
		if (!value.IsUse) {
			//�f�[�^��ǉ�
			value = _BoxInfo;
			return;
		}
	}
}

void CDebugManager::AddSphereInfo(SphereInfo _sphereInfo)
{
	for (SphereInfo& value : m_DebugSphereList)
	{
		if (!value.IsUse)
		{
			//�f�[�^�ǉ�
			value = _sphereInfo;
			return;
		}
	}
}

