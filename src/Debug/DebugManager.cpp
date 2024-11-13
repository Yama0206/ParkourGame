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
}

//デストラクタ
CDebugManager::~CDebugManager()
{

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

void CDebugManager::AddString(int _x, int _y, string _string)
{
	TextInfo value = { _x, _y, _string, DEFALUT_COLOR, true };

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

	TextInfo value = { _x, _y, buffer, DEFALUT_COLOR, true };

	AddTextInfo(value);

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

	for (TextInfo& value : m_TextInfoList)
	{
		if (value.IsUse) {
			DrawString(value.m_x, value.m_y, value.DebugString.c_str(), value.Color);
			//表示したら未使用にする
			value.IsUse = false;
		}
	}

	//球描画
	DrawSphere();
}

void CDebugManager::DrawSphere()
{
	for (int i = 0; i < m_DebugSphere.size(); ++i)
	{
		DrawSphere3D(m_DebugSphere[i].m_vPos, m_DebugSphere[i].m_fRad, m_DebugSphere[i].m_DivNum, m_DebugSphere[i].m_Color, m_DebugSphere[i].m_Color, false);
	}
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
