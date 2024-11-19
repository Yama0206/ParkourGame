#pragma once
#include "../HideObjectBase.h"

class CLocker : public HideObjectBase
{
private:
	VECTOR m_vPos;
	VECTOR m_vSize;
	VECTOR m_vRot;
	VECTOR m_vScale;

	int m_iHndl;
	float m_fRad;
public:
	//コンストラクタ

	//初期化
	void Init();
	//読み込み
	void Load();
	void Draw();
	void Fin();
	void Update();

public:

	
};