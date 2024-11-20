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
	//�R���X�g���N�^

	//������
	void Init();
	//�ǂݍ���
	void Load();
	void Draw();
	void Update();

public:
	VECTOR GetPos() { return m_vPos; }				//���W�擾
	void   SetPos(VECTOR vPos) { m_vPos = vPos; }	//���W�ݒ�
	float  GetRad() { return m_fRad; }				//���a
};