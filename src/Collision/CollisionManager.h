#pragma once
#include "../Enemy/EnemyManager.h"
#include "../shot/ShotManager.h"
#include "../Box/Box.h"
#include "../Player/Player.h"
#include "../Camera/PlayCamera.h"
#include "../Math/Hit.h"
#include "../Field/Field.h"
#include "../Box/FootBox.h"
#include "../Box/Rock.h"
#include "../Goal/Goal.h"
#include "../Item/Manager/ItemManager.h"
#include "../CheckPoint/Manager/CheckPointManager.h"
#include <vector>

using namespace std;

class CCollisionManager
{
public:
	//�@�G�ƒe�̓����蔻��
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									CShotManager& cShotManager);
	//���ƃv���C���[�̓����蔻��
	static void CheckHitBoxToPlayer(CPlayer& cPlayer,
									CBox& cBox);

	//	�t�B�[���h�ƃv���C���[�̓����蔻��
	static void CheckHitFieldToPlayer(CPlayer& cPlayer,
									 CField& cBackGround);

	//�v���C���[�Ƒ���̓����蔻��
	static void CheckHitPlayerToFootBox(CPlayer& cPlayer,
								vector<CFootBox>& cFBox);

	//�v���C���[�Ɛ΂̓����蔻��
	static void CheckHitPlayerToRock(CPlayer& cPlayer,
		vector<CRock>& cRock);

	//�v���C���[�ƃS�[���̓����蔻��
	static void CHeckHitPlayerToGoal(CPlayer& cPlayer,
									 CGoal& cGoal);

	//�v���C���[�ƃA�C�e���̂����蔻��
	static void CheckHitPlayerToItem(CPlayer& cPlayer,
									 CItemManager& cItemManager);

	//�v���C���[�ƃ`�F�b�N�|�C���g�̓����蔻��
	static void CheckHitPlayerToPoint(CPlayer& cPlayer,
									  CCheckPointManager& cCheckPointManager);


	//�}�E�X�|�C���^�ƃX�^�[�g�摜�̓����蔻��
	//static void CheckHitMouseToStartImg();

	//�v���C���[�ƃ{�b�N�X�̓����蔻��̃��C���\��
	static void PlayerToBoxLine(CPlayer& cPlayer,
								CBox& cBox);


};
