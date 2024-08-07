#pragma once
#include "DxLib.h"
#include "math.h"
#include "../Math/Math.h"

class CDebugCamera {
private:
	VECTOR	m_vCameraPos;	// �J�����̈ʒu
	VECTOR	m_vCameraRot;	// �J�����̒����_

public:
	// �R���X�g���N�^�A�f�X�g���N�^
	CDebugCamera();
	~CDebugCamera();

	// ������
	void Init();
	void Init(VECTOR vPos, float fRot = 0.0f);

	// ���t���[�����s���鏈��
	void Step();

	// �`��
	void Draw();

	// �X�V�����f�[�^�𔽉f
	void Update();
};