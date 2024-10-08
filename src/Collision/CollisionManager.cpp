#include "CollisionManager.h"

//�G�ƒe�̓����蔻��
void CCollisionManager::CheckHitShotToEnemy(CEnemyManager& cEnemyManager,
											CShotManager& cShotManager)
{
	//for (int i = 0; i < PL_SHOT_NUM; i++) {
	//	//�e�����擾���A���˂���Ă��Ȃ���Ύ���
	//	CShot& cPlayerShot = cShotManager.GetPlayerShot(i);
	//	if (!cPlayerShot.IsActiv()) { continue; }

	//	for (int j = 0; j < ENEMY_NUM; j++)
	//	{
	//		//�G�����擾���A��������Ă��Ȃ���Ύ���
	//		CEnemy& cEnemy = cEnemyManager.GetEnemy(j);
	//		if (!cEnemy.IsActiv()) { continue; }

	//		//���W�Ɣ��a���擾
	//		VECTOR vShotPos, vEnemyPos;
	//		float fShotRadius, fEnemyRadius;
	//		cPlayerShot.GetPotision(vShotPos);
	//		cEnemy.GetPosition(vEnemyPos);
	//		fShotRadius = cPlayerShot.GetRadius();
	//		fEnemyRadius = cEnemy.GetRadius();

	//		//�G�̂ق��͓����蔻��̒��S�𔼌a����������
	//		vEnemyPos.y += fEnemyRadius;

	//		//���ƒe�̓����蔻��
	//		if (CHit::IsHiSphere(vShotPos, fShotRadius, vEnemyPos, fEnemyRadius))
	//		{
	//			//�����܂ł���Γ�������
	//			cPlayerShot.HitCalc();
	//			cEnemy.HitCalc();
	//		}
	//	} 
	//}
}

//Box�ƃv���C���[�̓����蔻��
void CCollisionManager::CheckHitBoxToPlayer(CPlayer& cPlayer,
											CBox& cBox)
{
	//=========���E�̓����蔻��=========
	for (int i = 0; i < 1; i++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vPlayerPos, vBoxPos;					//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vBoxSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetPosition(vPlayerPos);			//�v���C���[���W�擾
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cBox.GetPotision(vBoxPos);					//�����W�擾
		vBoxSize = cBox.GetSize();					//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�Ɣ��̓����蔻��̃��C��
		PlayerToBoxLine(cPlayer, cBox);

		//�v���C���[�̈ړ����X���W������
		vPlayerColliPos.x = vPlayerNextPos.x;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//�E�����̓����蔻��
			if (DirArray[3]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vBoxPos.x + vBoxSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//�������̌v�Z
			if (DirArray[2]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vBoxPos.x - vBoxSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========���Ǝ�O�̓����蔻��=========
	for (int i = 0; i < 1; i++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vPlayerPos, vBoxPos;				//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;
		VECTOR vPlayerSize, vBoxSize;			//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetPosition(vPlayerPos);			//�v���C���[���W�擾
		cPlayer.GetNextPosVec(vPlayerNextPos);
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cBox.GetPotision(vBoxPos);				//�����W�擾
		vBoxSize = cBox.GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�Ɣ��̓����蔻��̃��C��
		PlayerToBoxLine(cPlayer, cBox);

		//�v���C���[�̈ړ����Z���W������
		vPlayerColliPos.z = vPlayerNextPos.z;

		//�����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//�������̌v�Z
			if (DirArray[4]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vBoxPos.z + vBoxSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//��O�����̌v�Z
			if (DirArray[5]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vBoxPos.z - vBoxSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========�㉺�̓����蔻��=========
	for (int i = 0; i < 1; i++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vPlayerPos, vBoxPos;				//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;
		VECTOR vPlayerSize, vBoxSize;			//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetPosition(vPlayerPos);			//�v���C���[���W�擾
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		
		//��
		cBox.GetPotision(vBoxPos);				//�����W�擾
		vBoxSize = cBox.GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�Ɣ��̓����蔻��̃��C��
		PlayerToBoxLine(cPlayer, cBox);

		//�v���C���[�̈ړ����Y���W������(���S���W���ق�������v���C���[�̍����̔����𑫂�)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vBoxPos, vBoxSize))
		{
			//�������̌v�Z
			if (DirArray[1]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vBoxPos.y + vBoxSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
			}
			//������̌v�Z
			if (DirArray[0]) {
				//�߂肱�ݗʌv�Z
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
	//=========���E�̓����蔻��=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vFBoxPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vFBoxSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);				//�����W�擾
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����X���W������
		vPlayerColliPos.x = vPlayerNextPos.x;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//�E�����̓����蔻��
			if (DirArray[3]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vFBoxPos.x + vFBoxSize.x / 2) - (vPlayerColliPos.x - vPlayerSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x + overlap);
			}
			//�������̌v�Z
			if (DirArray[2]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.x + vPlayerSize.x / 2) - (vFBoxPos.x - vFBoxSize.x / 2);
				cPlayer.SetNextPosX(vPlayerNextPos.x - overlap);
			}
		}

	}
	//=========���Ǝ�O�̓����蔻��=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vFBoxPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vFBoxSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾
		//��
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);				//�����W�擾
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����Z���W������
		vPlayerColliPos.z = vPlayerNextPos.z;

		//�����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//�������̌v�Z
			if (DirArray[4]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vFBoxPos.z + vFBoxSize.z / 2) - (vPlayerColliPos.z - vPlayerSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z + overlap);
				cPlayer.SetIsHitSide(true);
			}
			//��O�����̌v�Z
			if (DirArray[5]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vPlayerColliPos.z + vPlayerSize.z / 2) - (vFBoxPos.z - vFBoxSize.z / 2);
				cPlayer.SetNextPosZ(vPlayerNextPos.z - overlap);
			}
		}
		else {
			cPlayer.SetIsHitSide(false);
		}
	}

	//=========�㉺�̓����蔻��=========
	for (int FBoxIndex = 0; FBoxIndex < cFBox.size(); FBoxIndex++) {
		//�����`�F�b�N�p�ϐ�
		bool DirArray[6];
		memset(DirArray, false, sizeof(DirArray));

		//���W�Ɣ��a������ϐ�
		VECTOR vFBoxPos;							//���W
		VECTOR vPlayerNextPos, vPlayerColliPos;		//�ړ���̍��W�A�����蔻����Ƃ���W
		VECTOR vPlayerSize, vFBoxSize;				//�T�C�Y

		//���W�Ɣ��a���擾
		//�v���C���[
		cPlayer.GetNextPosVec(vPlayerNextPos);		//�v���C���[�̈ړ���̍��W
		cPlayer.GetCenterPos(vPlayerColliPos);		//�v���C���[�̌��_���W
		cPlayer.GetSize(vPlayerSize);				//�v���C���[�T�C�Y�擾

		//��
		cFBox[FBoxIndex].GetCenterPos(vFBoxPos, 10.0f);			//�����W�擾
		vFBoxSize = cFBox[FBoxIndex].GetSize();				//���T�C�Y�擾

		//�v���C���[�̐i��ł�������擾
		cPlayer.GetMoveDir(DirArray);

		//�v���C���[�̈ړ����Y���W������(���S���W���ق�������v���C���[�̍����̔����𑫂�)
		vPlayerColliPos.y = vPlayerNextPos.y + PLAYER_HALF_HEIGHT;

		//�̓����蔻��
		if (CHit::IsHitRect(vPlayerColliPos, vPlayerSize, vFBoxPos, vFBoxSize))
		{
			//�������̌v�Z
			if (DirArray[1]) {
				//�߂肱�ݗʌv�Z
				float overlap = (vFBoxPos.y + vFBoxSize.y / 2) - (vPlayerColliPos.y - vPlayerSize.y / 2);
				cPlayer.SetNextPosY(vPlayerNextPos.y + overlap);
				cPlayer.SetIsHitLength(true);
				cPlayer.SetIsJamp(false);
			}
			//������̌v�Z
			if (DirArray[0]) {
				//�߂肱�ݗʌv�Z
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

void CCollisionManager::CheckHitPlayerToPoint(CPlayer& cPlayer)
{
	for (int CheckPointIndex = 0; CheckPointIndex < CCheckPointManager::GetInstance()->GetCheckPointSize(); CheckPointIndex++) {
		//�`�F�b�N�|�C���g�}�l�[�W���[���擾
		CCheckPoint* cCheckPoint = CCheckPointManager::GetInstance()->GetCheckPoint(CheckPointIndex);

		VECTOR vPlayerPos, vCheckPointPos;		//���W
		float fPlayerRad, fCheckPointRad;		//���a

		//�擾
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
		//�G�l�~�[�N���X�擾
		CEnemy* cEnemy = cEnemyManager.GetEnemy(EnemyIndex);

		VECTOR vEnemyPos, vCheckPointPos;		//���W
		float fEnemyRad, fCheckPointRad;		//���a

		//�擾
		cEnemy->GetPosition(vEnemyPos);
		vCheckPointPos = CCheckPointManager::GetInstance()->GetPosVec(cEnemy->GetCPNum());
		fEnemyRad = cEnemy->GetRadius();
		fCheckPointRad = CCheckPointManager::GetInstance()->GetfRad(cEnemy->GetCPNum());

		DrawSphere3D(vEnemyPos, fEnemyRad, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), false);
		DrawSphere3D(vCheckPointPos, fCheckPointRad, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), true);

		//�G���������ĂȂ������������蔻����Ƃ�
		if (SphereCollision(fEnemyRad, vEnemyPos, fCheckPointRad, vCheckPointPos))
		{
			cEnemy->SetCPNum( CCheckPointManager::GetInstance()->GetNextNum(GetRand(4), cEnemy->GetCPNum()));
		}
	}
}

//void CCollisionManager::CheckHitBoxToCamera(CPlayerCamera& cPlayerCamera,
//											CBox& cBox)
//{
//	VECTOR vPlayerCameraPos, vBoxPos;		//���W�p�ϐ�
//	VECTOR vPlayerCameraSize, vBoxSize;		//�T�C�Y�p�ϐ�
//	bool DirArray[6];
//
//	//�����Ǘ��̕ϐ��̏�����
//	memset(DirArray, false, sizeof(DirArray));
//
//	//���W
//	vPlayerCameraPos = cPlayerCamera.GetPosVEC();		//�v���C���[
//	cBox.GetPotision(vBoxPos);							//��
//
//	//�T�C�Y
//	vPlayerCameraSize = CAMERA_SIZE;					//�v���C���[
//	vBoxSize = cBox.GetHalfSize();						//��
//}

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
