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
#include "../Debug/DebugManager.h"
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
									 CField& cBackGround);

	//プレイヤーと足場の当たり判定
	static void CheckHitPlayerToFootBox(CPlayer& cPlayer,
								vector<CFootBox>& cFBox);

	//プレイヤーと石の当たり判定
	static void CheckHitPlayerToRock(CPlayer& cPlayer,
		vector<CRock>& cRock);

	//プレイヤーとゴールの当たり判定
	static void CHeckHitPlayerToGoal(CPlayer& cPlayer,
									 CGoal& cGoal);

	//プレイヤーとアイテムのあたり判定
	static void CheckHitPlayerToItem(CPlayer& cPlayer,
									 CItemManager& cItemManager);

	//プレイヤーとチェックポイントの当たり判定
	static void CheckHitPlayerToPoint(CPlayer& cPlayer, CEnemyManager& cEnemyManager);

	//敵とチェックポイントの当たり判定
	static void CheckHitEnemyToPoint(CEnemyManager& cEnemyManager);

	//プレイヤーと敵の当たり判定
	static void CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager);


	//マウスポインタとスタート画像の当たり判定
	//static void CheckHitMouseToStartImg();

	//プレイヤーとボックスの当たり判定のライン表示
	static void PlayerToBoxLine(CPlayer& cPlayer,
								CBox& cBox);


};
