#include "ShotManager.h"

//��`�֘A
static const char PLSHOT_MODEL_PATH[] = { "data/shot/plshot.x" };

//�R���X�g���N�^
CShotManager::CShotManager()
{
}

//�f�X�g���N�^
CShotManager::~CShotManager()
{
}

//������
void CShotManager::Init()
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Init();
	}
}

void CShotManager::Load()
{
	//�I���W�i�����f���̓ǂݍ���
	int iHndl = MV1LoadModel(PLSHOT_MODEL_PATH);
	//���f���𕡐�
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Load(iHndl);
	}
	//�I���W�i���폜
	MV1DeleteModel(iHndl);
}

//�I������
void CShotManager::Fin()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Fin();
	}
}

//�ʏ폈��
void CShotManager::Step()
{
	for (int i = 0; i < PL_SHOT_NUM; i++) {
		cPlayerShot[i].Step();
	}
}

//�X�V����
void CShotManager::Draw()
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		cPlayerShot[i].Draw();
	}
}

//�v���C���[�V���b�g���N�G�X�g
void CShotManager::RequestPlayerShot(const VECTOR& vPos, const VECTOR& vSpeed)
{
	for (int i = 0; i < PL_SHOT_NUM; i++)
	{
		if (cPlayerShot[i].RequestShot(vPos, vSpeed))
		{
			CSoundManager::Play(CSoundManager::SOUNDID_SE_PLSHOT);
			break;
		}
	}
}

