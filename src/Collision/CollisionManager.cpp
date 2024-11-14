#include "CollisionManager.h"
#include <Windows.h>
#include <string>


void CCollisionManager::CheckHitFieldToPlayer(CPlayer& cPlayer,
											  CField& cField)
{
	VECTOR vPlCenter;
	float fRadius;

	cPlayer.GetNextPosVec(vPlCenter);
	fRadius = cPlayer.GetRadius();

	cPlayer.ReflectCollision(cField.HitCheck(vPlCenter, fRadius));
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

void CCollisionManager::CheckHitPlayerToPoint(CPlayer& cPlayer, CEnemyManager& cEnemyManager)
{
	for (int EnemyIndex = 0; EnemyIndex < cEnemyManager.GetEnemySize(); EnemyIndex++) {
		//エネミークラス取得
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);
		//チェックポイントの数分for文を回す
		for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetSize(); CheckPointIndex++) 
		{
			VECTOR vPlayerPos, vCheckPointPos;		//座標
			float fPlayerRad, fCheckPointRad;		//半径
			int Num;

			//プレイヤーとチェックポイント情報取得
			cPlayer.GetPosition(vPlayerPos);
			vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex);
			fPlayerRad = cPlayer.GetRadius();
			fCheckPointRad = CCheckPointManager::GetInstance()->GetRad(CheckPointIndex);
			
			if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vCheckPointPos.x, vCheckPointPos.z, fCheckPointRad))
			{
				//一つ前に通った場所とは当たり判定をとらない
				if (CCheckPointManager::GetInstance()->GetLastPassedPlayerNum() == CheckPointIndex) {
					continue;
				}
				CCheckPointManager::GetInstance()->SetLastPassedPlayerNum(CheckPointIndex);
				//プレイヤーが通った場所を保存
				CCheckPointManager::GetInstance()->SetPassedPlayerNum(CheckPointIndex);
			}		
			//デバッグ文字描画
			CDebugManager::GetInstance()->AddFormatString(900, 0, "プレイヤーが最後通った場所 = %d", CCheckPointManager::GetInstance()->GetLastPassedPlayerNum());
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

		int NextCheckPointArrayIndex = -1;
		int DebugNum = 0;
		
		//取得
		cEnemy->GetPosition(vEnemyPos);
		fEnemyRad = cEnemy->GetRadius();
		for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetSize(); CheckPointIndex++) {
			vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex);
			fCheckPointRad = CCheckPointManager::GetInstance()->GetRad(CheckPointIndex);

			//敵が到着してないチェックポイントだけ当たり判定をとる
			if (SphereCollision(fEnemyRad, vEnemyPos, fCheckPointRad, vCheckPointPos) && CCheckPointManager::GetInstance()->GetLastPassedEnemyNum() != CheckPointIndex)
			{
				//通った場所を保存
				CCheckPointManager::GetInstance()->SetLastPassedEnemyNum(CheckPointIndex);
				cEnemy->SetLastPassedCheckPoint(CheckPointIndex);

				//プレイヤーを見つけていないときだけこの中の処理を行う
				if (cEnemy->GetState() == Patrol) {
					//ランダムで配列の引数を取得
					//配列の引数がほしいので値を-1する
					NextCheckPointArrayIndex = GetRand(CCheckPointManager::GetInstance()->GetArrayIndex(CheckPointIndex) - 1);
					NextCheckPointArrayIndex = CCheckPointManager::GetInstance()->GetNextCurrentNum(CheckPointIndex, NextCheckPointArrayIndex);

					//次に向かう場所を設定
					cEnemy->SetNextCheckPointNum(NextCheckPointArrayIndex);
				}
			}
		}
	}
}

void CCollisionManager::CheckHitPlayerToEnemy(CPlayer& cPlayer, CEnemyManager& cEnemyManager)
{
	for (int EnemyIndex = 0; EnemyIndex < cEnemyManager.GetEnemySize(); EnemyIndex++)
	{
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);

		cEnemy->SetOldState(cEnemy->GetState());

		VECTOR vPlayerPos, vEnemyPos;															//座標
		float fPlayerRad, fEnemyTrackingRad, fEnemySearchRad, fEnemyTrackingPlayerRad;			//半径

		memset(&vPlayerPos, 0.0f, sizeof(VECTOR));
		memset(&vEnemyPos, 0.0f, sizeof(VECTOR));
		fPlayerRad = 0.0f;
		fEnemyTrackingRad = 0.0f;
		fEnemySearchRad = 0.0f;
		fEnemyTrackingPlayerRad = 0.0f;

		cPlayer.GetPosition(vPlayerPos);
		cEnemy->GetPosition(vEnemyPos);
		fPlayerRad = cPlayer.GetRadius();
		fEnemyTrackingRad = cEnemy->GetTrackingRad();
		fEnemySearchRad = cEnemy->GetSearchRad();
		fEnemyTrackingPlayerRad = cEnemy->GetTrackingPlayerRad();

		//索敵範囲のあたり判定
		if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemySearchRad)) {
			//一つでも通った場所があれば
			if (CCheckPointManager::GetInstance()->GetPassedPlayerNumSize() != -1){
				//追跡モード(チェックポイント)
				cEnemy->SetState(TrackingCheckPoint);
			}
			//プレイヤーが通った最後の場所がすでに通った場所かどこも通ってない場合
			else {
				//プレイヤーを直接追跡する
				cEnemy->SetState(TrackingPlayer);
			}
		}		

		//敵がプレイヤーを直接追いかける範囲
		if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemyTrackingPlayerRad))
		{
			//プレイヤーを直接追いかける
			cEnemy->SetState(TrackingPlayer);
		}
		//追跡範囲の当たり判定
		//この範囲より外にプレイヤーが出た場合巡回モードに戻す
		else if (!IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemyTrackingRad)){
		
		//範囲外の場合
		//巡回モード
			//切り替わるとき配列を削除
			CCheckPointManager::GetInstance()->ClearPassedPlayerNum();

			//巡回モードに変更
			cEnemy->SetState(Patrol);
		}

	}
}

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
