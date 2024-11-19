#pragma once
#include "DxLib.h"

class CModel {
protected:
	enum Anim_State {
		ANIMSTATE_NORMAL,
		ANIMSTATE_LOOP,
		ANIMSTATE_END,
	};

	//�A�j���֘A�̃f�[�^���܂Ƃ߂��\����
	struct ANIM_DATA {
		float m_fEndFrm;			//�A�j���̑S�Đ�����
		float m_fFrm;				//�A�j���̍Đ�����
		float m_fSpd;				//�A�j���̍Đ����x
		float m_fRate;				//�A�j���̃u�����h��
		int m_iHndl;				//�A�j���n���h��
		int m_iID;					//�Đ����̃A�j��
		int m_iState;				//�A�j���̏��
	};

	struct OLD_ANIM_DATA {
		float m_fEndFrm;			//�A�j���̑S�Đ�����
		float m_fFrm;				//�A�j���̍Đ�����
		float m_fSpd;				//�A�j���̍Đ����x
		int m_iHndl;				//�A�j���n���h��
		int m_iID;					//�Đ����̃A�j��
		int m_iState;				//�A�j���̏��
	};

	VECTOR m_vPos;					//���W
	VECTOR m_vNextPos;				//�X�V��̍��W
	VECTOR m_vSpd;					//�ړ����x
	VECTOR m_vRot;					//��]�p�x
	VECTOR m_vScale;				//�g��k����
	VECTOR m_vSize;					//�c�A���A���s��
	ANIM_DATA m_sAnimData;			//�A�j���Đ��֘A�f�[�^
	ANIM_DATA m_sOldAnimData;	//�X�V�O�̃A�j���Đ��֘A�f�[�^

	int	  m_iHndl;					//���f���n���h��

	bool m_IsAllive;				//�����t���O

public:
	//������
	virtual void Init();
	//���l�̍X�V
	virtual void Update();
	//���f���`��
	virtual void Draw();
	//�I������
	virtual void Exit();

	//�摜�ǂݍ��݊֘A
	//���f���ʏ탍�[�h
	bool LoadModel(const char* pFileName);
	//���f���R�s�[���[�h
	//��memo		:	���łɓǂݍ���ł��郂�f���𕡐��\���������ꍇ�Ɏg�p���܂�
	//iSrcHndl		:	�ǂݍ��݂������f���̃n���h��
	bool DupilicateModel(int iSrcHndl);
	//���f���f�[�^�̍폜
	void DeleteModel();

	//�A�j���[�V�����֘A

	//�A�j���A�b�v�f�[�g
	//@memo		:	�A�j���X�V�����A����ǂ�ł�������
	void UpdateAnim();

	//�A�j��
	void UpdateBlendRate();

	//�A�j�����N�G�X�g
	// iAnimId		:	�A�^�b�`����A�j���ԍ�
	// iAnimSpd		:	�A�j���Đ����x
	// iAnimSrcHndl	:	�A�j���[�V�����������Ă��郂�f���̃n���h��(-1�Ȃ�΂��̃��f���̃A�j���g�p)
	// NameCheck	:	�ʃ��f���̃A�j�����g�p����ꍇ�A���f���̃t���[��������v���Ă��Ȃ��ꍇ
	//					�A�j�����A�^�b�`���邩(iAnimSrcHndl=-1�̏ꍇ�͖���)
	void Request(int AnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//���[�v�A�j�����N�G�X�g
	//��memo		:	�A�j���ŏI�t���[���ɂȂ�����ŏ��ɖ߂�܂�
	void RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//�G���h���[�v�A�j�����N�G�X�g
	//@memo		:	�A�j�����ŏI�t���[���ɂȂ�t�炻�̂܂܂Ŏ~�܂�܂�
	void RequestendLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

private:
	//���S�ɃA�j�����Ń^�b�`
	void DetachAnim();
};
