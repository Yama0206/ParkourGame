#include "DebugManager.h"

CDebugManager* CDebugManager::m_Instance = NULL;

//定義
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
	//NULLでないなら削除
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = NULL;	//削除したらNULL代入
	}
}

//コンストラクタ
CDebugManager::CDebugManager()
{
	//リストの初期化
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

//デストラクタ
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
	//フォーマット済み文字列を格納するバッファ
	char buffer[CHAR_SIZE];

	//可変引数を処理
	va_list args;
	va_start(args, format);
	//フォーマット済みの文字列を生成する
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
	//フォーマット済み文字列を格納するバッファ
	char buffer[CHAR_SIZE];

	//可変引数を処理
	va_list args;
	va_start(args, format);
	//フォーマット済みの文字列を生成する
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	DrawLogString(buffer);
}

void CDebugManager::Draw()
{
	if (!IsDeBug) { return; }

	//デバッグ文言
	for (TextInfo& value : m_TextInfoList)
	{
		if (value.IsUse) {
			DrawString(value.m_x, value.m_y, value.DebugString.c_str(), value.Color);
			//表示したら未使用にする
			value.IsUse = false;
		}
	}

	//デバッグボックス
	for (BoxInfo& value : m_DebugBoxList)
	{
		if (value.IsUse) {
			DrawBox3D(value.m_vPos, value.m_vSize, value.ColorUp, value.ColorDown, value.ColorSide);
			//表示したら未使用にする
			value.IsUse = false;
		}
	}

	//デバッグ球
	for (SphereInfo& value : m_DebugSphereList)
	{
		if (value.IsUse) {
			DrawSphere3D(value.m_vPos, value.m_fRad, value.m_DivNum, value.m_Color, value.m_Color, false);
			//表示したら未使用にする
			value.IsUse = false;
		}
	}
}

void CDebugManager::DrawBox3D(VECTOR Pos, VECTOR Size, unsigned int ColorUp, unsigned int ColorDown, unsigned int ColorSide)
{

	//サイズの半分をとる
	VECTOR HalfSize = VScale(Size, 0.5f);

	/*上の面*/
	//左から右(手前)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), ColorUp);
	//左から右(奥)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);
	//左手前から左奥
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);
	//右手前から右奥
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), ColorUp);

	/*下の面*/
	//左から右(手前)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorDown);
	//左から右(奥)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);
	//左手前から左奥
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);
	//右手前から右奥
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorDown);

	/*側面*/
	//手前左(上から下)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorSide);
	//手前右(上から下)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z - HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z - HalfSize.z), ColorSide);
	//奥左(上から下)
	DrawLine3D(VGet(Pos.x - HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x - HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorSide);
	//奥右(上から下)
	DrawLine3D(VGet(Pos.x + HalfSize.x, Pos.y + HalfSize.y, Pos.z + HalfSize.z), VGet(Pos.x + HalfSize.x, Pos.y - HalfSize.y, Pos.z + HalfSize.z), ColorSide);
}

void CDebugManager::AddTextInfo(TextInfo _textInfo)
{
	for (TextInfo& value : m_TextInfoList)
	{
		if (!value.IsUse) {
			//データを追加
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
			//データを追加
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
			//データ追加
			value = _sphereInfo;
			return;
		}
	}
}

