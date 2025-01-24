#pragma once
#include "DxLib.h"

//�萔
constexpr int STAGE1_COIN = 10;			//�X�e�[�W1�R�C���̖���
constexpr int STAGE2_COIN = 10;			//�X�e�[�W2�R�C���̖���
constexpr int STAGE3_COIN = 10;			//�X�e�[�W3�R�C���̖���

class CGameSystem 
{
private:
	//�C���X�^���X
	static CGameSystem* m_Instance; 

	float m_fTimePosX;					//���Ԃ�\������X���W
	float m_fTimePosY;					//���Ԃ�\������Y���W

	float m_fFreamPosX;					//�t���[����\������X���W
	float m_fFreamPosY;					//�t���[����\������Y���W

	//�����o�ϐ�
	int m_iFreamCnt;					//�t���[���J�E���g�ϐ�
	int m_iTimeCnt;						//���ԃJ�E���g�ϐ�

	int m_PlayerLife;					//�v���C���[�̎c�@

	int m_CoinNum;						//�R�C���擾����

	//�t���O
	bool m_IsClear;						//�N���A�����𖞂��������ǂ���

public:

	//�V���O���g���̃N���X�擾�Ɣj��--------------
//CCheckPointManager���擾
	static CGameSystem* GetInstance();
	//CCheckPointManager���폜
	static void DeleteInstance();
	//--------------------------------------------

public:
	//�ǂݍ���
	void Load();
	//�`��
	void Draw();

	//�t���[�����J�E���g����
	void CntFream();

	//���Ԃ��J�E���g����֐�
	void CntTime();

	//�R�C���̎擾�����J�E���g
	void CntCoinNum() { m_CoinNum++; };

	//�N���A����
	void ClearDecision();

};