#include "Player.h"

//定義関連
static const float VIEWPOINT_SPEED = 0.1f;					//プレイヤーの回転速度
static const float MOVE_SPEED = 1.0f;						//プレイヤーの移動速度
static const float ADD_SPEED = 0.2f;						//プレイヤーのスピードを加算する
static const float SAB_SPEED = 0.1f; 						//プレイヤーのスピードを減算する
static const float DASH_SPEED = 2.0f;						//プレイヤーが走った時の移動速度
static const float GRAVITY = 0.2f;							//プレイヤーの重力
static const float MAX_GRAVITY = 3.0f;						//プレイヤーの重力の限界
static const float MIN_GRAVITY = 0.1f;						//プレイヤーの重力の最低
static const float YSPEED = 4.0f;							//プレイヤーのY方向のスピード
static const float ROTATE_SPEED = 0.1f;						//回転スピード

	
//コンストラクタ
CPlayer::CPlayer()
{
	//ひとまず初期化していく
	m_eState = PLAYER_STATE_NORMAL;				//プレイヤーの状態
}
//デストラクタ
CPlayer::~CPlayer()
{
	//ひとまず安全そうな値を入れておく
	Delete();
	Fin();
}

//初期値設定
void CPlayer::InitValue()
{
	//列挙型
	m_eState = PLAYER_STATE_NORMAL;				//プレイヤーの状態
	m_eDir = FRONT;								//プレイヤーの方向

	//変数
	memset(&m_ViewRot, 0.0f, sizeof(m_ViewRot));					
	m_fMoveSpeed = 0.0f;										
	m_fChangeRot = 0.0f;											
	m_fGravity = GRAVITY;											

	//フラグ
	memset(&m_IsHit, false, sizeof(bool));						
	memset(&m_IsHitLength, false, sizeof(bool));
	memset(&m_IsKeyHit, false, sizeof(bool));				
	memset(&m_IsJump, false, sizeof(bool));						

	m_vPos.y = 100.0f;
}

//毎フレーム呼ぶ処理
void CPlayer::Step(CShotManager& cShotManager, CCameraManager& cCameraManager)
{
	if (m_IsAllive) {
		switch (m_sAnimData.m_iID)
		{
		case ANIMID_DEFAULT:
			ExecDefault();
			break;
		case ANIMID_WALK:
			ExecWalk();
			break;
		case ANIMID_RUN:
			ExecRun();
			break;
			//case ANIMID_WAIT:
			//	ExecWait();
			//	break;
			//case ANIMID_UPDOWN:
			//	ExecUpDown();
			//	break;
			//case ANIMID_SHAKE:
			//	ExecShake();
			//	break;
			//case ANIMID_PIANO:
			//	ExecPiano();
			//	break;
			//case ANIMID_DANCE:
			//	ExecDance();
			//	break;
		}
		//弾の発射関数
		Shot(cShotManager);
		//操作関数
		Control(cCameraManager.GetPlayCamRot());
		//ジャンプ処理
		Jamp();
		//重力処理
		Gravity();
	}

}

//データ関連の破棄
void CPlayer::Delete()
{
	if (m_iHndl != -1)
	{
		MV1DeleteModel(m_iHndl);
		m_iHndl = -1;
	}
}

//終了処理
void CPlayer::Fin()
{
	//実はプレイヤーも今のところ必須処理はない
	//確保していたメモリを解放するなどを記述するとよい
}

//進んでいる方向チェック
void CPlayer::GetMoveDir(bool* _DirArray)
{
	//右方向のチェック
	if (m_vNextPos.x < m_vPos.x) {
		_DirArray[RIGHT] = true;
	}
	//左方向チェック　
	if (m_vNextPos.x > m_vPos.x) {
		_DirArray[LEFT] = true;
	}
	//下方向チェック
	if (m_vNextPos.y < m_vPos.y) {
		_DirArray[DOWN] = true;
	}
	//上方向チェック
	if (m_vNextPos.y > m_vPos.y) {
		_DirArray[UP] = true;
	}
	//奥方向チェック
	if (m_vNextPos.z < m_vPos.z) {
		_DirArray[FRONT] = true;
	}
	//手前方向チェック
	if (m_vNextPos.z > m_vPos.z) {
		_DirArray[BACK] = true;
	}
}

//プレイヤーの向きを変える
void CPlayer::ChangeDir(int FreamCnt)
{
	//Wキー押したとき
	//進行方向に回転させる
	if (FreamCnt % 60 == 0 && m_fChangeRot > -180.0f) {
		//1F事に30度回転
		m_fChangeRot -= 30;
	}
	//回転しきったら
	if (m_fChangeRot > -180)
	{
		//キーを押したフラグを折る
		m_IsKeyHit = false;
	}
}

//操作関数
void CPlayer::Control(VECTOR vRot)
{
	//プレイヤーのフレームカウント用変数
	int FreamCnt = 0;			

	//移動しているかのチェック
	m_vNextPos = m_vPos;

	//何かのキーが押されたら
	if (m_IsKeyHit) {
		//フレームをカウント
		FreamCnt++;
	}

	//キャラクターの回転
	//float fRot = 0.0f;

	////シフトキーが押されたら
	//if (CInput::IsKeyKeep(KEY_INPUT_LSHIFT))
	//{
	//	//プレイヤーのスピードが最大値になるまでスピードを足す
	//	if (m_fMoveSpeed < DASH_SPEED) {
	//		//少しずつ足していく
	//		m_fMoveSpeed += ADD_SPEED;
	//	}		
	//}
	//else {
	//	//通常スピードまで少しずつ減らす
	//	if (m_fMoveSpeed > MOVE_SPEED) {
	//		m_fMoveSpeed -= ADD_SPEED;
	//	}	
	//}

	//Wキーが押されたとき
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		//キーが押されたフラグON
		m_IsKeyHit = true;

		//座標移動
		m_fMoveSpeed -= ADD_SPEED;
	
		//最大値を決定
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = DX_PI_F;
		//モデルを回転させる
		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		m_fMoveSpeed -= ADD_SPEED;

		if (m_fMoveSpeed < MOVE_SPEED)
		{
			m_fMoveSpeed = -MOVE_SPEED;
		}
		fRot = 0.0f * DX_PI_F / 180.0f;

		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		//座標移動
		m_fMoveSpeed -= ADD_SPEED;

		//最大値を決定
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = 90.0f * DX_PI_F / 180.0f;

		m_ViewRot.y = vRot.y + fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D)) 
	{
		m_fMoveSpeed -= ADD_SPEED;

		if (m_fMoveSpeed < MOVE_SPEED)
		{
			m_fMoveSpeed = -MOVE_SPEED;
		}

		fRot = -90.0f * DX_PI_F / 180.0f;

		m_ViewRot.y = vRot.y + fRot;
	}
	else {
		if (fabs(m_fMoveSpeed) > 0.01f) {
			m_fMoveSpeed *= 0.9;
		}
		else {
			m_fMoveSpeed = 0.0f;
		}
		m_IsKeyHit = false;
		FreamCnt = 0;
	}
	

	//入力したキー情報とプレイヤーの角度から移動速度を求める
	//移動ベクトルの計算
	m_vSpd.x = sinf(vRot.y + fRot) * m_fMoveSpeed;
	m_vSpd.z = cosf(vRot.y + fRot) * m_fMoveSpeed;

	//移動速度を現在の座標に加算する
	m_vNextPos.x += m_vSpd.x;
	m_vNextPos.z += m_vSpd.z;
}

//ジャンプ処理
void CPlayer::Jamp()
{
	//スペースキーを押したとき
	if (CInput::IsKeyPush(KEY_INPUT_SPACE) && !m_IsJump)
	{
		//m_IsJump = true;
		m_vSpd.y = YSPEED;
	}
}

//重力処理
void CPlayer::Gravity()
{
	//プレイヤーの重力の上限
	//プレイヤーが物体に当たっているときは重力を止める
	
	if (!m_IsHitLength) {
		if (m_vSpd.y > -MAX_GRAVITY) {
			m_vSpd.y -= m_fGravity;
		}
	}

	//プレイヤーのY座標にプレイヤーのYスピードを代入
	m_vNextPos.y += m_vSpd.y;
}

//弾の発射
void CPlayer::Shot(CShotManager &cShotManager)
{
	if (CInput::IsKeyPush(KEY_INPUT_Z))
	{
		//プレイヤーの体から出るように座標を上げる
		VECTOR vPos = m_vPos;
		vPos.y += 5.0f;
		//速度はプレイヤーと同じ方法で移動方向を決める
		VECTOR vSpd;
		const float SHOT_SPEED = 5.0f;
		vSpd.x = sinf(m_vRot.y) * - SHOT_SPEED;
		vSpd.z = cosf(m_vRot.y) * - SHOT_SPEED;
		vSpd.y = 0.0f;
		cShotManager.RequestPlayerShot(vPos, vSpd);
	}
}

void CPlayer::Update()
{
	//1F前のプレイヤーの座標を更新する
	m_vPos = m_vNextPos;

	MV1SetRotationXYZ(m_iHndl, m_ViewRot);
	MV1SetPosition(m_iHndl, m_vPos);
}

void CPlayer::Draw()
{
	if (m_IsAllive) {
		MV1DrawModel(m_iHndl);
	}
}

//何もしていないとき
void CPlayer::ExecDefault()
{
	//Wキーを押したとき
	if (CInput::IsKeyKeep(KEY_INPUT_W) || CInput::IsKeyKeep(KEY_INPUT_S) || CInput::IsKeyKeep(KEY_INPUT_D) || CInput::IsKeyKeep(KEY_INPUT_A))
	{
		//シフトキーを押しているとき
		if (CInput::IsKeyKeep(KEY_INPUT_LSHIFT))
		{
			RequestLoop(ANIMID_RUN, 1.0f);
		}
		//押していないときは歩く
		else {
			RequestLoop(ANIMID_WALK, 1.0f);
		}
	}
	else if (CInput::IsKeyPush(KEY_INPUT_Z))
	{
		//Zキーをぶらぶらする
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
}

//歩いているとき
void CPlayer::ExecWalk()
{
	//Wキーを話したとき
	if (CInput::IsKeyRelease(KEY_INPUT_W) || CInput::IsKeyRelease(KEY_INPUT_S) || CInput::IsKeyRelease(KEY_INPUT_D) || CInput::IsKeyRelease(KEY_INPUT_A))
	{
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
	//シフトキーを押しているとき
	if (CInput::IsKeyKeep(KEY_INPUT_LSHIFT))
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
}

//走っているとき
void CPlayer::ExecRun()
{
	//Wキーを話したとき
	if (CInput::IsKeyRelease(KEY_INPUT_W) || CInput::IsKeyRelease(KEY_INPUT_S) || CInput::IsKeyRelease(KEY_INPUT_D) || CInput::IsKeyRelease(KEY_INPUT_A))
	{
		RequestLoop(ANIMID_DEFAULT, 1.0f);
	}
}

//サイズ取得
void CPlayer::GetSize(VECTOR& vSize)
{
	 vSize = m_vSize;
}

//サイズ設定
VECTOR CPlayer::SetSize()
{
	return m_vSize = { PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH };
}

//プレイヤーの移動後座標設定
void CPlayer::SetNextPosX(float vNextPosX)
{
	m_vNextPos.x = vNextPosX;
}
void CPlayer::SetNextPosY(float vNextPosY)
{
	m_vNextPos.y = vNextPosY;
}
void CPlayer::SetNextPosZ(float vNextPosZ)
{
	m_vNextPos.z = vNextPosZ;
}
//プレイヤーの座標設定
void CPlayer::SetPosX(float vPosX)
{
	m_vPos.x = vPosX;
}
void CPlayer::SetPosY(float vPosY)
{
	m_vPos.y = vPosY;
}
void CPlayer::SetPosZ(float vPosZ)
{
	m_vPos.z = vPosZ;
}

void CPlayer::ReflectCollision(VECTOR vAddVec)
{
	//オールゼロなら何もしない
	if(vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;

	m_vNextPos = VAdd(vAddVec, m_vNextPos);

	//当たった時は重力処理をしない
	/*m_fGravity = 0.0f;*/
}

//中心座標取得
void CPlayer::GetCenterPos(VECTOR& vPos)
{
	vPos = VAdd(m_vPos, VGet(0.0f, PLAYER_HALF_HEIGHT, 0.0f));
}

//半分のサイズを取得
void CPlayer::GetHalfSize(VECTOR& vHalfSize)
{
	vHalfSize = DivVec(m_vSize, 2.0f);
}
