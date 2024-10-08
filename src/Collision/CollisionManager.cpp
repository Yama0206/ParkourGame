#include "CollisionManager.h"

//敵と弾の当たり判定
void CCollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
											CShotManager& cShotManager)
{
	//for (int i = 0; i < PL_SHOT_NUM; i++) {
	//	//弾情報を取得し、発射されていなければ次へ
	//	CShot& cPlayerShot = cShotManager.GetPlayerShot(i);
	//	if (!cPlayerShot.IsActiv()) { continue; }

	//	for (int j = 0; j < ENEMY_NUM; j++)
	//	{
	//		//敵情報を取得し、生成されていなければ次へ
	//		CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
	//		if (!cEnemy.IsActiv()) { continue; }

	//		//座標と半径を取得
	//		VECTOR vShotPos, vEnemyPos;
	//		float fShotRadius, fEnemyRadius;
	//		cPlayerShot.GetPotision(vShotPos);
	//		cEnemy.GetPosition(vEnemyPos);
	//		fShotRadius = cPlayerShot.GetRadius();
	//		fEnemyRadius = cEnemy.GetRadius();

	//		//敵のほうは当たり判定の中心を半径分浮かせる
	//		vEnemyPos.y += fEnemyRadius;

	//		//球と弾の当たり判定
	//		if (CHit::IsHiSphere(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
	//		{
	//			//ここまでくれば当たった
	//			cPlayerShot.HitCalc();
	//			cEnemy.HitCalc();
	//		}
	//	} 
	//}
}

//Boxとプレイヤーの当たり判定
void CCollisionManager::CheckHitBoxToPlayer(CPlayer& cPlayer,
											CBox& cBox)
{
	//=========左右の当たり判定=========
	for (int i = 0; i < 1; i++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vPlayerPos, vBoxPos;					//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vBoxSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetPosition(vPlayerPos);			//プレイヤー座標取得
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cBox.GetPotision(vBoxPos);					//箱座標取得
		vBoxSize = cBox.GetSize();					//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーと箱の当たり判定のライン
		PlayerToBoxLine(cPlayer, cBox);

		//プレイヤーの移動後のX座標を入れる
		vPlayerColliPos.x = vPlayerNextPos.x;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//右方向の当たり判定
			if (DirArray[3]) {
				//めりこみ量計算
				float overlap = (vBoxPos.x + vBoxSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//左方向の計算
			if (DirArray[2]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vBoxPos.x - vBoxSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========奥と手前の当たり判定=========
	for (int i = 0; i < 1; i++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vPlayerPos, vBoxPos;				//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;
		VECTOR vPlayerSize, vBoxSize;			//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetPosition(vPlayerPos);			//プレイヤー座標取得
		cPlayer.GetNextPosVec(vPlayerNextPos);
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cBox.GetPotision(vBoxPos);				//箱座標取得
		vBoxSize = cBox.GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーと箱の当たり判定のライン
		PlayerToBoxLine(cPlayer, cBox);

		//プレイヤーの移動後のZ座標を入れる
		vPlayerColliPos.z = vPlayerNextPos.z;

		//当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//奥方向の計算
			if (DirArray[4]) {
				//めりこみ量計算
				float overlap = (vBoxPos.z + vBoxSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//手前方向の計算
			if (DirArray[5]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vBoxPos.z - vBoxSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========上下の当たり判定=========
	for (int i = 0; i < 1; i++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vPlayerPos, vBoxPos;				//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;
		VECTOR vPlayerSize, vBoxSize;			//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetPosition(vPlayerPos);			//プレイヤー座標取得
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		
		//箱
		cBox.GetPotision(vBoxPos);				//箱座標取得
		vBoxSize = cBox.GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーと箱の当たり判定のライン
		PlayerToBoxLine(cPlayer, cBox);

		//プレイヤーの移動後のY座標を入れる(中心座標がほしいからプレイヤーの高さの半分を足す)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//下方向の計算
			if (DirArray[1]) {
				//めりこみ量計算
				float overlap = (vBoxPos.y + vBoxSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
			}
			//上方向の計算
			if (DirArray[0]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.y + vPlayerSize.y / 2) - (vBoxPos.y - vBoxSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y - overlap);
				cPlayer.SetIsHitLength(true);
			}
		}
		else {
			cPlayer.SetIsHitLength(false);
		}
	}
}

void CCollisionManager::CheckHitFieldToPlayer(CPlayer& cPlayer,
											  CField& cField)
{
	VECTOR vPlCenter;
	float fRadius;

	cPlayer.GetNextPosVec(vPlCenter);
	fRadius = cPlayer.GetRadius();

	cPlayer.ReflectCollision(cField.HitCheck(vPlCenter, fRadius));
}

void CCollisionManager::CheckHitPlayerToFootBox(CPlayer& cPlayer,
												vector<CFootBox>& cFBox)
{
	//=========左右の当たり判定=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vFBoxPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vFBoxSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);				//箱座標取得
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のX座標を入れる
		vPlayerColliPos.x = vPlayerNextPos.x;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//右方向の当たり判定
			if (DirArray[3]) {
				//めりこみ量計算
				float overlap = (vFBoxPos.x + vFBoxSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//左方向の計算
			if (DirArray[2]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vFBoxPos.x - vFBoxSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========奥と手前の当たり判定=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vFBoxPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vFBoxSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);				//箱座標取得
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のZ座標を入れる
		vPlayerColliPos.z = vPlayerNextPos.z;

		//当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//奥方向の計算
			if (DirArray[4]) {
				//めりこみ量計算
				float overlap = (vFBoxPos.z + vFBoxSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//手前方向の計算
			if (DirArray[5]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vFBoxPos.z - vFBoxSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========上下の当たり判定=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vFBoxPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vFBoxSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得

		//箱
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);			//箱座標取得
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のY座標を入れる(中心座標がほしいからプレイヤーの高さの半分を足す)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//下方向の計算
			if (DirArray[1]) {
				//めりこみ量計算
				float overlap = (vFBoxPos.y + vFBoxSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
				cPlayer.SetIsJamp(false);
			}
			//上方向の計算
			if (DirArray[0]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.y + vPlayerSize.y / 2) - (vFBoxPos.y - vFBoxSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y - overlap);
				cPlayer.SetIsJamp(false);
			}
		}
		else {
			cPlayer.SetIsHitLength(false);
		}
	}
}

void CCollisionManager::CheckHitPlayerToRock(CPlayer& cPlayer,
											 vector<CRock>& cRock)
{
	//=========左右の当たり判定=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vRockPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vRockSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cRock[RockIndex].GetCenterPos(vRockPos, 10.0f);				//箱座標取得
		vRockSize = cRock[RockIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のX座標を入れる
		vPlayerColliPos.x = vPlayerNextPos.x;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//右方向の当たり判定
			if (DirArray[3]) {
				//めりこみ量計算
				float overlap = (vRockPos.x + vRockSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//左方向の計算
			if (DirArray[2]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vRockPos.x - vRockSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========奥と手前の当たり判定=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vRockPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vRockSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得
		//箱
		cRock[RockIndex].GetCenterPos(vRockPos, 10.0f);				//箱座標取得
		vRockSize = cRock[RockIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のZ座標を入れる
		vPlayerColliPos.z = vPlayerNextPos.z;

		//当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//奥方向の計算
			if (DirArray[4]) {
				//めりこみ量計算
				float overlap = (vRockPos.z + vRockSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//手前方向の計算
			if (DirArray[5]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vRockPos.z - vRockSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========上下の当たり判定=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//方向チェック用変数
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//座標と半径を入れる変数
		VECTOR vRockPos;							//座標
		VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
		VECTOR vPlayerSize, vRockSize;				//サイズ

		//座標と半径を取得
		//プレイヤー
		cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
		cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
		cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得

		//箱
		cRock[RockIndex].GetCenterPos(vRockPos, 5.0f);		//箱座標取得
		vRockSize = cRock[RockIndex].GetSize();				//箱サイズ取得

		//プレイヤーの進んでいる方向取得
		cPlayer.GetMoveDir(DirArray);

		//プレイヤーの移動後のY座標を入れる(中心座標がほしいからプレイヤーの高さの半分を足す)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//の当たり判定
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//下方向の計算
			if (DirArray[1]) {
				//めりこみ量計算
				float overlap = (vRockPos.y + vRockSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
			}
			//上方向の計算
			if (DirArray[0]) {
				//めりこみ量計算
				float overlap = (vPlayerColliPos.y + vPlayerSize.y / 2) - (vRockPos.y - vRockSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y - overlap);
			}
		}
		else {
			cPlayer.SetIsHitLength(false);
		}
	}
}

void CCollisionManager::CHeckHitPlayerToGoal(CPlayer& cPlayer, CGoal& cGoal)
{
	//方向チェック用変数
	bool DirArray[6];
	memset(DirArray, false, sizeof(DirArray));

	//座標と半径を入れる変数
	VECTOR vGoalPos;							//座標
	VECTOR vPlayerNextPos, vPlayerColliPos;		//移動後の座標、当たり判定をとる座標
	VECTOR vPlayerSize, vGoalSize;				//サイズ

	//座標と半径を取得
	//プレイヤー
	cPlayer.GetNextPosVec(vPlayerNextPos);		//プレイヤーの移動後の座標
	cPlayer.GetCenterPos(vPlayerColliPos);		//プレイヤーの原点座標
	cPlayer.GetSize(vPlayerSize);				//プレイヤーサイズ取得

	//箱
	cGoal.GetCenterPos(vGoalPos, 5.0f);		//箱座標取得
	vGoalSize = cGoal.GetSize();				//箱サイズ取得

	//プレイヤーの進んでいる方向取得
	cPlayer.GetMoveDir(DirArray);

	//プレイヤーの移動後のY座標を入れる(中心座標がほしいからプレイヤーの高さの半分を足す)
	vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

	//の当たり判定
	if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vGoalPos, vGoalSize))
	{
		cGoal.SetIsGoal(true);
	}
	else {
		cPlayer.SetIsHitLength(false);
	}
}

void CCollisionManager::CheckHitPlayerToItem(CPlayer& cPlayer,
											 CItemManager& cItemManager)
{
	//アイテムの総数分for分を回す
	for (int ItemIndex = 0; ItemIndex < cItemManager.GetItemSize(); ItemIndex++) {

		//アイテムリストクラス取得
		CItemBase* cItem = cItemManager.GetItem(ItemIndex);

		//当たり判定用変数
		VECTOR vColliPlayerPos, vNextPlayerPos;			//プレイヤー座標
		VECTOR vItemPos;								//アイテム座標
		VECTOR vPlayerSize, vItemSize;					//サイズ

		memset(&vColliPlayerPos, 0.0, sizeof(VECTOR));
		memset(&vNextPlayerPos, 0.0, sizeof(VECTOR));
		memset(&vPlayerSize, 0.0, sizeof(VECTOR));
		memset(&vItemPos, 0.0, sizeof(VECTOR));
		memset(&vItemSize, 0.0, sizeof(VECTOR));

		//座標取得
		cPlayer.GetCenterPos(vColliPlayerPos);			//プレイヤーの中心座標
		cPlayer.GetNextPosVec(vNextPlayerPos);			//プレイヤーの移動後の座標
		cPlayer.GetSize(vPlayerSize);

		vItemPos = cItem->GetPosVec();			//アイテムに座標を代入
		vItemSize = cItem->GetSizeVec();		//アイテムにサイズを代入

		//プレイヤーとアイテムが当たったかどうか
		if (IsHitRect(vColliPlayerPos, vPlayerSize, vItemPos, vItemSize))
		{
			//アイテムの生存フラグをOFF
			cItem->SetIsAllive(false);
		}
	}

}

void CCollisionManager::CheckHitPlayerToPoint(CPlayer& cPlayer)
{
	for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetCheckPointSize(); CheckPointIndex++) {
		//チェックポイントマネージャーを取得
		CCheckPoint* cCheckPoint = CCheckPointManager::GetInstance()->GetCheckPoint(CheckPointIndex);

		VECTOR vPlayerPos, vCheckPointPos;		//座標
		float fPlayerRad, fCheckPointRad;		//半径

		//取得
		cPlayer.GetCenterPos(vPlayerPos);
		vCheckPointPos = cCheckPoint->GetPosVec();
		fPlayerRad = cPlayer.GetRadius();
		fCheckPointRad = cCheckPoint->GetRad();

		if(SphereCollision(fPlayerRad, vPlayerPos, fCheckPointRad, vCheckPointPos))
		{
			cCheckPoint[CheckPointIndex].SetIsArrived(true);
		}
	}
}

void CCollisionManager::CheckHitEnemyToPoint(CEnemyManager& cEnemyManager)
{
	for (int EnemyIndex = 0; EnemyIndex < cEnemyManager.GetEnemySize(); EnemyIndex++) {
		//エネミークラス取得
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);

		VECTOR vEnemyPos, vCheckPointPos;		//座標
		float fEnemyRad, fCheckPointRad;		//半径

		//取得
		cEnemy->GetPosition(vEnemyPos);
		vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(cEnemy->GetCPNum());
		fEnemyRad = cEnemy->GetRadius();
		fCheckPointRad = CCheckPointManager::GetInstance()->GetfRad(cEnemy->GetCPNum());

		DrawSphere3D(vEnemyPos, fEnemyRad, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), false);
		DrawSphere3D(vCheckPointPos, fCheckPointRad, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), true);

		//敵が到着してない時だけ当たり判定をとる
		if (SphereCollision(fEnemyRad, vEnemyPos, fCheckPointRad, vCheckPointPos))
		{
			cEnemy->SetCPNum( CCheckPointManager::GetInstance()->GetNextNum(GetRand(4), cEnemy->GetCPNum()));
		}
	}
}

//void CCollisionManager::CheckHitBoxToCamera(CPlayerCamera& cPlayerCamera,
//											CBox& cBox)
//{
//	VECTOR vPlayerCameraPos, vBoxPos;		//座標用変数
//	VECTOR vPlayerCameraSize, vBoxSize;		//サイズ用変数
//	bool DirArray[6];
//
//	//方向管理の変数の初期化
//	memset(DirArray, false, sizeof(DirArray));
//
//	//座標
//	vPlayerCameraPos = cPlayerCamera.GetPosVEC();		//プレイヤー
//	cBox.GetPotision(vBoxPos);							//箱
//
//	//サイズ
//	vPlayerCameraSize = CAMERA_SIZE;					//プレイヤー
//	vBoxSize = cBox.GetHalfSize();						//箱
//}

void CCollisionManager::PlayerToBoxLine(CPlayer& cPlayer,
										CBox& cBox)
{
	//座標と半径を取得
	VECTOR vPlayerPos, vBoxPos;
	VECTOR vPlayerSize, vBoxSize;
	cPlayer.GetPosition(vPlayerPos);
	cBox.GetPotision(vBoxPos);

	vPlayerPos.y += 9.0;

	VECTOR v_StartposX = vPlayerPos;	//X軸始点
	VECTOR v_FinposX = vPlayerPos;		//X軸終点
	VECTOR v_StartposY = vPlayerPos;	//Y軸始点
	VECTOR v_FinposY = vPlayerPos;		//Y軸終点
	VECTOR v_StartposZ = vPlayerPos;	//Z軸始点
	VECTOR v_FinposZ = vPlayerPos;		//Z軸終点

	v_StartposX.x -= 5.0f;
	v_FinposX.x += 5.0f;

	v_StartposY.y -= 9.0f;
	v_FinposY.y += 9.0f;

	v_StartposZ.z -= 5.0f;
	v_FinposZ.z += 5.0f;

	DrawLine3D(v_StartposX, v_FinposX, GetColor(255, 0, 0));				//X方向
	DrawLine3D(v_StartposY, v_FinposY, GetColor(0, 255, 0));				//Y方向
	DrawLine3D(v_StartposZ, v_FinposZ, GetColor(0, 0, 0));				//Z方向

	VECTOR v_StartBposX = vBoxPos;		//X軸始点
	VECTOR v_FinBposX = vBoxPos;		//X軸終点
	VECTOR v_StartBposY = vBoxPos;		//Y軸始点
	VECTOR v_FinBposY = vBoxPos;		//Y軸終点
	VECTOR v_StartBposZ = vBoxPos;		//Z軸始点
	VECTOR v_FinBposZ = vBoxPos;		//Z軸終点

	v_StartBposX.x -= 8.0f;
	v_FinBposX.x += 8.0f;

	v_StartBposY.y -= 8.0f;
	v_FinBposY.y += 8.0f;

	v_StartBposZ.z -= 8.0f;
	v_FinBposZ.z += 8.0f;

	DrawLine3D(v_StartBposX, v_FinBposX, GetColor(255, 0, 0));				//X方向
	DrawLine3D(v_StartBposY, v_FinBposY, GetColor(0, 255, 0));				//Y方向
	DrawLine3D(v_StartBposZ, v_FinBposZ, GetColor(0, 0, 0));				//Z方向

	DrawLine3D(VGet(0, 16.0f, 0.0f), VGet(8.0f, 16.0f, 0.0f), GetColor(0,255,0));
}
