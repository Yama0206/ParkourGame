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
	//フィールド
public:
	//	フィールドとプレイヤーの当たり判定
	static void CheckHitFieldToPlayer(CPlayer& cPlayer, CField& cBackGround);
	//フィールドと敵の当たり判定
	static void CheckHitEnemyToField(CEnemyManager& cEnemyManager, CField& cField);

	//プレイヤー関連
public:
	//プレイヤーと石の当たり判定
	static void CheckHitPlayerToRock(CPlayer& cPlayer, vector<CRock>& cRock);
	//プレイヤーとパルクールオブジェクトの当たり判定
	static void CheckHitPlayerToParkourObject(CPlayer& cPlayer, CBox& cBox);
	//プレイヤーとゴールの当たり判定
	static void CHeckHitPlayerToGoal(CPlayer& cPlayer, CGoal& cGoal);
	//プレイヤーとアイテムのあたり判定
	static void CheckHitPlayerToItem(CPlayer& cPlayer, CItemManager& cItemManager);
	//プレイヤーとチェックポイントの当たり判定
	static void CheckHitPlayerToPoint(CPlayer& cPlayer, CEnemyManager& cEnemyManager);
	//プレイヤーと敵の当たり判定
	static void CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager);
	//プレイヤーと隠れる用オブジェクトとの当たり判定
	static void CheckHitPlayerToHideObject(CPlayer& cPlayer, CLocker& cLocker);

	//敵関連
public:
	//敵とチェックポイントの当たり判定
	static void CheckHitEnemyToPoint(CEnemyManager& cEnemyManager);

	//デバッグ
public:
	//プレイヤーとボックスの当たり判定のライン表示
	static void PlayerToBoxLine(CPlayer& cPlayer,
								CBox& cBox);


};
