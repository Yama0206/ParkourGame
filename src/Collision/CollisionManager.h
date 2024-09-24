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
#include <vector>

using namespace std;

class CCollisionManager
{
public:
	//　敵と弾の当たり判定
	static void CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
									CShotManager& cShotManager);
	//箱とプレイヤーの当たり判定
	static void CheckHitBoxToPlayer(CPlayer& cPlayer,
									CBox& cBox);

	//	フィールドとプレイヤーの当たり判定
	static void CheckHitFieldToPlayer(CPlayer& cPlayer,
									 BackGround& cBackGround);

	//プレイヤーと足場の当たり判定
	static void CheckHitPlayerToFootBox(CPlayer& cPlayer,
								vector<CFootBox>& cFBox);

	//プレイヤーと石の当たり判定
	static void CheckHitPlayerToRock(CPlayer& cPlayer,
		vector<CRock>& cRock);

	//プレイヤーとゴールの当たり判定
	static void CHeckHitPlayerToGoal(CPlayer& cPlayer,
									 CGoal& cGoal);

	//アイテムとプレイヤーのあたり判定
	static void CheckHitPlayerToItem(CPlayer& cPlayer,
									 CItemManager& cItemManager);

	//マウスポインタとスタート画像の当たり判定
	//static void CheckHitMouseToStartImg();

	//プレイヤーとボックスの当たり判定のライン表示
	static void PlayerToBoxLine(CPlayer& cPlayer,
								CBox& cBox);


};
