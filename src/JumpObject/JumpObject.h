#pragma once
#include "../Object/Object.h"


class CJumpObject : public CObject
{
private:
	bool m_IsHit;			//あったかどうか
public:
	//初期設定
	void InitValue();
	//通常処理
	void Step();

	
public:
	//関数
	VECTOR GetvSize() { return m_vSize; }	//サイズ
	VECTOR GetPos() { return m_vPos; }		//座標
};