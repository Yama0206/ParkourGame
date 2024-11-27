#pragma once
#include "../Enemy/Manager/EnemyManager.h"
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
#include "../Debug/DebugManager.h"
#include "../HideObject/Locker/Locker.h"
#include <vector>

using namespace std;

class CCollisionManager
{
	//�t�B�[���h
public:
	//	�t�B�[���h�ƃv���C���[�̓����蔻��
	static void CheckHitFieldToPlayer(CPlayer& cPlayer, CField& cBackGround);
	//�t�B�[���h�ƓG�̓����蔻��
	static void CheckHitEnemyToField(CEnemyManager& cEnemyManager, CField& cField);

	//�v���C���[�֘A
public:
	//�v���C���[�Ɛ΂̓����蔻��
	static void CheckHitPlayerToRock(CPlayer& cPlayer, vector<CRock>& cRock);
	//�v���C���[�ƃp���N�[���I�u�W�F�N�g�̓����蔻��
	static void CheckHitPlayerToParkourObject(CPlayer& cPlayer, CBox& cBox);
	//�v���C���[�ƃS�[���̓����蔻��
	static void CHeckHitPlayerToGoal(CPlayer& cPlayer, CGoal& cGoal);
	//�v���C���[�ƃA�C�e���̂����蔻��
	static void CheckHitPlayerToItem(CPlayer& cPlayer, CItemManager& cItemManager);
	//�v���C���[�ƃ`�F�b�N�|�C���g�̓����蔻��
	static void CheckHitPlayerToPoint(CPlayer& cPlayer, CEnemyManager& cEnemyManager);
	//�v���C���[�ƓG�̓����蔻��
	static void CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager);
	//�v���C���[�ƉB���p�I�u�W�F�N�g�Ƃ̓����蔻��
	static void CheckHitPlayerToHideObject(CPlayer& cPlayer, CLocker& cLocker);

	//�G�֘A
public:
	//�G�ƃ`�F�b�N�|�C���g�̓����蔻��
	static void CheckHitEnemyToPoint(CEnemyManager& cEnemyManager);

	//�f�o�b�O
public:
	//�v���C���[�ƃ{�b�N�X�̓����蔻��̃��C���\��
	static void PlayerToBoxLine(CPlayer& cPlayer,
								CBox& cBox);


};
