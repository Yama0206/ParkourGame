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
	//=========���E�̓����蔻��=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vRockPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vRockSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cRock[RockIndex].GetCenterPos(vRockPos, 10.0f);				//�����W�擾
		vRockSize = cRock[RockIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����X���W������
		vPlayerColliPos.x = vPlayerNextPos.x;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//�E�����̓����蔻��
			if (DirArray[3]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vRockPos.x + vRockSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//�������̌v�Z
			if (DirArray[2]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vRockPos.x - vRockSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========���Ǝ�O�̓����蔻��=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vRockPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vRockSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cRock[RockIndex].GetCenterPos(vRockPos, 10.0f);				//�����W�擾
		vRockSize = cRock[RockIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����Z���W������
		vPlayerColliPos.z = vPlayerNextPos.z;

		//�����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//�������̌v�Z
			if (DirArray[4]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vRockPos.z + vRockSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//��O�����̌v�Z
			if (DirArray[5]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vRockPos.z - vRockSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========�㉺�̓����蔻��=========
	for (int RockIndex = 0; RockIndex < cRock.size(); RockIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vRockPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vRockSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾

		//��
		cRock[RockIndex].GetCenterPos(vRockPos, 5.0f);		//�����W�擾
		vRockSize = cRock[RockIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����Y���W������(���S���W���ق�������v���C���[�̍����̔����𑫂�)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vRockPos, vRockSize))
		{
			//�������̌v�Z
			if (DirArray[1]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vRockPos.y + vRockSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
			}
			//������̌v�Z
			if (DirArray[0]) {
				//�߂肱�ݗʌv�Z
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
	//�����`�F�b�N�p�ϐ�
	bool DirArray[6];
	memset(DirArray, false, sizeof(DirArray));

	//���W�Ɣ��a������ϐ�
	VECTOR vGoalPos;							//���W
	VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
	VECTOR vPlayerSize, vGoalSize;				//�T�C�Y

	//���W�Ɣ��a���擾
	//�v���C���[
	cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
	cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
	cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾

	//��
	cGoal.GetCenterPos(vGoalPos, 5.0f);		//�����W�擾
	vGoalSize = cGoal.GetSize();				//���T�C�Y�擾

	//�v���C���[�̐i��ł�������擾
	cPlayer.GetMoveDir(DirArray);

	//�v���C���[�̈ړ����Y���W������(���S���W���ق�������v���C���[�̍����̔����𑫂�)
	vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

	//�̓����蔻��
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
	//�A�C�e���̑�����for������
	for (int ItemIndex = 0; ItemIndex < cItemManager.GetItemSize(); ItemIndex++) {

		//�A�C�e�����X�g�N���X�擾
		CItemBase* cItem = cItemManager.GetItem(ItemIndex);

		//�����蔻��p�ϐ�
		VECTOR vColliPlayerPos, vNextPlayerPos;			//�v���C���[���W
		VECTOR vItemPos;								//�A�C�e�����W
		VECTOR vPlayerSize, vItemSize;					//�T�C�Y

		memset(&vColliPlayerPos, 0.0, sizeof(VECTOR));
		memset(&vNextPlayerPos, 0.0, sizeof(VECTOR));
		memset(&vPlayerSize, 0.0, sizeof(VECTOR));
		memset(&vItemPos, 0.0, sizeof(VECTOR));
		memset(&vItemSize, 0.0, sizeof(VECTOR));

		//���W�擾
		cPlayer.GetCenterPos(vColliPlayerPos);			//�v���C���[�̒��S���W
		cPlayer.GetNextPosVec(vNextPlayerPos);			//�v���C���[�̈ړ���̍��W
		cPlayer.GetSize(vPlayerSize);

		vItemPos = cItem->GetPosVec();			//�A�C�e���ɍ��W����
		vItemSize = cItem->GetSizeVec();		//�A�C�e���ɃT�C�Y����

		//�v���C���[�ƃA�C�e���������������ǂ���
		if (IsHitRect(vColliPlayerPos, vPlayerSize, vItemPos, vItemSize))
		{
			//�A�C�e���̐����t���O��OFF
			cItem->SetIsAllive(false);
		}
	}

}

void CCollisionManager::CheckHitPlayerToPoint(CPlayer& cPlayer, CEnemyManager& cEnemyManager)
{
	for (int EnemyIndex = 0; EnemyIndex < cEnemyManager.GetEnemySize(); EnemyIndex++) {
		//�G�l�~�[�N���X�擾
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);
		//�`�F�b�N�|�C���g�̐���for������
		for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetSize(); CheckPointIndex++) 
		{
			VECTOR vPlayerPos, vCheckPointPos;		//���W
			float fPlayerRad, fCheckPointRad;		//���a
			int Num;

			//�v���C���[�ƃ`�F�b�N�|�C���g���擾
			cPlayer.GetPosition(vPlayerPos);
			vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex);
			fPlayerRad = cPlayer.GetRadius();
			fCheckPointRad = CCheckPointManager::GetInstance()->GetRad(CheckPointIndex);
			
			if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vCheckPointPos.x, vCheckPointPos.z, fCheckPointRad))
			{
				//��O�ɒʂ����ꏊ�Ƃ͓����蔻����Ƃ�Ȃ�
				if (CCheckPointManager::GetInstance()->GetLastPassedPlayerNum() == CheckPointIndex) {
					continue;
				}
				CCheckPointManager::GetInstance()->SetLastPassedPlayerNum(CheckPointIndex);
				//�v���C���[���ʂ����ꏊ��ۑ�
				CCheckPointManager::GetInstance()->SetPassedPlayerNum(CheckPointIndex);
			}		
			//�f�o�b�O�����`��
			CDebugManager::GetInstance()->AddFormatString(900, 0, "�v���C���[���Ō�ʂ����ꏊ = %d", CCheckPointManager::GetInstance()->GetLastPassedPlayerNum());
		} 
	}
}

void CCollisionManager::CheckHitEnemyToPoint(CEnemyManager& cEnemyManager)
{
	for (int EnemyIndex = 0; EnemyIndex < cEnemyManager.GetEnemySize(); EnemyIndex++) {
		//�G�l�~�[�N���X�擾
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);

		VECTOR vEnemyPos, vCheckPointPos;		//���W
		float fEnemyRad, fCheckPointRad;		//���a

		int NextCheckPointArrayIndex = -1;
		int DebugNum = 0;
		
		//�擾
		cEnemy->GetPosition(vEnemyPos);
		fEnemyRad = cEnemy->GetRadius();
		for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetSize(); CheckPointIndex++) {
			vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(CheckPointIndex);
			fCheckPointRad = CCheckPointManager::GetInstance()->GetRad(CheckPointIndex);

			//�G���������ĂȂ��`�F�b�N�|�C���g���������蔻����Ƃ�
			if (SphereCollision(fEnemyRad, vEnemyPos, fCheckPointRad, vCheckPointPos) && CCheckPointManager::GetInstance()->GetLastPassedEnemyNum() != CheckPointIndex)
			{
				//�ʂ����ꏊ��ۑ�
				CCheckPointManager::GetInstance()->SetLastPassedEnemyNum(CheckPointIndex);
				cEnemy->SetLastPassedCheckPoint(CheckPointIndex);

				//�v���C���[�������Ă��Ȃ��Ƃ��������̒��̏������s��
				if (cEnemy->GetState() == Patrol) {
					//�����_���Ŕz��̈������擾
					//�z��̈������ق����̂Œl��-1����
					NextCheckPointArrayIndex = GetRand(CCheckPointManager::GetInstance()->GetArrayIndex(CheckPointIndex) - 1);
					NextCheckPointArrayIndex = CCheckPointManager::GetInstance()->GetNextCurrentNum(CheckPointIndex, NextCheckPointArrayIndex);

					//���Ɍ������ꏊ��ݒ�
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

		VECTOR vPlayerPos, vEnemyPos;															//���W
		float fPlayerRad, fEnemyTrackingRad, fEnemySearchRad, fEnemyTrackingPlayerRad;			//���a

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

		//���G�͈͂̂����蔻��
		if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemySearchRad)) {
			//��ł��ʂ����ꏊ�������
			if (CCheckPointManager::GetInstance()->GetPassedPlayerNumSize() != -1){
				//�ǐՃ��[�h(�`�F�b�N�|�C���g)
				cEnemy->SetState(TrackingCheckPoint);
			}
			//�v���C���[���ʂ����Ō�̏ꏊ�����łɒʂ����ꏊ���ǂ����ʂ��ĂȂ��ꍇ
			else {
				//�v���C���[�𒼐ڒǐՂ���
				cEnemy->SetState(TrackingPlayer);
			}
		}		

		//�G���v���C���[�𒼐ڒǂ�������͈�
		if (IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemyTrackingPlayerRad))
		{
			//�v���C���[�𒼐ڒǂ�������
			cEnemy->SetState(TrackingPlayer);
		}
		//�ǐՔ͈͂̓����蔻��
		//���͈̔͂��O�Ƀv���C���[���o���ꍇ���񃂁[�h�ɖ߂�
		else if (!IsHitCircle(vPlayerPos.x, vPlayerPos.z, fPlayerRad, vEnemyPos.x, vEnemyPos.z, fEnemyTrackingRad)){
		
		//�͈͊O�̏ꍇ
		//���񃂁[�h
			//�؂�ւ��Ƃ��z����폜
			CCheckPointManager::GetInstance()->ClearPassedPlayerNum();

			//���񃂁[�h�ɕύX
			cEnemy->SetState(Patrol);
		}

	}
}

void CCollisionManager::PlayerToBoxLine(CPlayer& cPlayer,
										CBox& cBox)
{
	//���W�Ɣ��a���擾
	VECTOR vPlayerPos, vBoxPos;
	VECTOR vPlayerSize, vBoxSize;
	cPlayer.GetPosition(vPlayerPos);
	cBox.GetPotision(vBoxPos);

	vPlayerPos.y += 9.0;

	VECTOR v_StartposX = vPlayerPos;	//X���n�_
	VECTOR v_FinposX = vPlayerPos;		//X���I�_
	VECTOR v_StartposY = vPlayerPos;	//Y���n�_
	VECTOR v_FinposY = vPlayerPos;		//Y���I�_
	VECTOR v_StartposZ = vPlayerPos;	//Z���n�_
	VECTOR v_FinposZ = vPlayerPos;		//Z���I�_

	v_StartposX.x -= 5.0f;
	v_FinposX.x += 5.0f;

	v_StartposY.y -= 9.0f;
	v_FinposY.y += 9.0f;

	v_StartposZ.z -= 5.0f;
	v_FinposZ.z += 5.0f;

	DrawLine3D(v_StartposX, v_FinposX, GetColor(255, 0, 0));				//X����
	DrawLine3D(v_StartposY, v_FinposY, GetColor(0, 255, 0));				//Y����
	DrawLine3D(v_StartposZ, v_FinposZ, GetColor(0, 0, 0));				//Z����

	VECTOR v_StartBposX = vBoxPos;		//X���n�_
	VECTOR v_FinBposX = vBoxPos;		//X���I�_
	VECTOR v_StartBposY = vBoxPos;		//Y���n�_
	VECTOR v_FinBposY = vBoxPos;		//Y���I�_
	VECTOR v_StartBposZ = vBoxPos;		//Z���n�_
	VECTOR v_FinBposZ = vBoxPos;		//Z���I�_

	v_StartBposX.x -= 8.0f;
	v_FinBposX.x += 8.0f;

	v_StartBposY.y -= 8.0f;
	v_FinBposY.y += 8.0f;

	v_StartBposZ.z -= 8.0f;
	v_FinBposZ.z += 8.0f;

	DrawLine3D(v_StartBposX, v_FinBposX, GetColor(255, 0, 0));				//X����
	DrawLine3D(v_StartBposY, v_FinBposY, GetColor(0, 255, 0));				//Y����
	DrawLine3D(v_StartBposZ, v_FinBposZ, GetColor(0, 0, 0));				//Z����

	DrawLine3D(VGet(0, 16.0f, 0.0f), VGet(8.0f, 16.0f, 0.0f), GetColor(0,255,0));
}
