#include "Player.h"

//定義関連
static constexpr float VIEWPOINT_SPEED = 0.1f;					//プレイヤーの回転速度
static constexpr float MOVE_SPEED = 1.0f;						//プレイヤーの移動速度
static constexpr float ADD_SPEED = 0.2f;						//プレイヤーのスピードを加算する
static constexpr float SAB_SPEED = 0.1f; 						//プレイヤーのスピードを減算する
static constexpr float DASH_SPEED = 2.0f;						//プレイヤーが走った時の移動速度
static constexpr float GRAVITY = 0.2f;							//プレイヤーの重力
static constexpr float MAX_GRAVITY = 2.0f;						//プレイヤーの重力の限界
static constexpr float MIN_GRAVITY = 0.1f;						//プレイヤーの重力の最低
static constexpr float YSPEED = 4.5f;							//プレイヤーのY方向のスピード
static constexpr float ROTATE_SPEED = 0.1f;						//回転スピード
static constexpr float SCALE = 0.1f;							//拡大縮小率
	
//コンストラクタ
CPlayer::CPlayer()
{
	//ひとまず初期化していく
	m_sAnimData.m_iID = ANIMID_DEFAULT;				//プレイヤーの状態
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
	m_sAnimData.m_iID = ANIMID_DEFAULT;				//プレイヤーの状態
	m_sOldAnimData.m_iID = ANIMID_DEFAULT;			//1Fのプレイヤーの状態
	m_eDir = FRONT;									//プレイヤーの方向

	//変数
	memset(&m_ViewRot, 0.0f, sizeof(m_ViewRot));	
	m_vScale = { SCALE , SCALE , SCALE };
	m_PadXBuf = 0;
	m_PadYBuf = 0;
	m_fMoveSpeed = 0.0f;										
	m_fChangeRot = 0.0f;											
	m_fGravity = GRAVITY;											

	//フラグ
	m_IsHit = false;
	m_IsHitLength = false;
	m_IsKeyHit = false;
	m_IsGround = false;
	m_IsHide = false;
	m_IsHitHideObject = false;

	m_vPos.y = 10.0f;
}

//毎フレーム呼ぶ処理
void CPlayer::Step(CShotManager& cShotManager, CCameraManager& cCameraManager)
{
	CDebugManager::GetInstance()->AddFormatString(700, 120, "プレイヤー座標　X = %f, Y = %f, Z = %f", m_vPos.x, m_vPos.y, m_vPos.z);
	CDebugManager::GetInstance()->AddFormatString(700, 140, "%d",m_sAnimData.m_iID);
	CDebugManager::GetInstance()->AddFormatString(700, 160, "%f",m_sAnimData.m_fEndFrm);
	CDebugManager::GetInstance()->AddFormatString(700, 180, "%f", m_sAnimData.m_fFrm);
	CDebugManager::GetInstance()->AddFormatString(700, 200, "%f", m_sAnimData.m_fSpd);
	CDebugManager::GetInstance()->AddFormatString(700, 220, "%d", m_sAnimData.m_iState);
	CDebugManager::GetInstance()->AddFormatString(700, 240, "プレイヤーの着地フラグ = %d", m_IsGround);
	CDebugManager::GetInstance()->AddFormatString(700, 260, "プレイヤーのスピード X = %f,Y = %f,Z = %f", m_vSpd.x,m_vSpd.y,m_vSpd.z);
	CDebugManager::GetInstance()->AddFormatString(700, 280, "Y = %f", m_vNextPos.y);
	CDebugManager::GetInstance()->AddFormatString(700, 300, "グラビティー = %f", m_fGravity);

	if (m_IsAllive) {
		//プレイヤーのアニメーション情報を保存しておく
		m_sOldAnimData = m_sAnimData;

		//移動しているかのチェック
		m_vNextPos = m_vPos;

		//左スティックの情報を取得
		GetJoypadAnalogInput(&m_PadXBuf, &m_PadYBuf, DX_INPUT_PAD1);

		switch (m_sAnimData.m_iID)
		{
		case ANIMID_DEFAULT:
			ExecDefault();
			break;

		case ANIMID_WAIT:
			ExecWait();
			break;

		case ANIMID_RUN:
			ExecRun();
			break;

		case ANIMID_FAST_RUN:
			ExecFastRun();
			break;

		case ANIMID_JUMP:
			ExecJump();
			break;

		case ANIMID_RUNNINGJUMP:
			ExecRunningJump();
			break;

		case ANIMID_HIDE:
			ExecHide();
			break;
			
		/*case ANIMID_UPDOWN:
			ExecUpDown();
			break;
		case ANIMID_SHAKE:
			ExecShake();
			break;
		case ANIMID_PIANO:
			ExecPiano();
			break;
		case ANIMID_DANCE:
			ExecDance();
			break;
		*/
		}
		if (CInput::IsKeyPush(KEY_INPUT_SPACE))
		{
			m_vNextPos.y += 10;
		}

		//左スティック傾きでプレイヤーを回転させる
		PadRotation(cCameraManager.GetPlayCamRot());

		//移動ベクトルを計算
		CalcMoveVec(cCameraManager.GetPlayCamRot());

		//移動量加算
		AddMove();
	}

}

void CPlayer::Update()
{
	//1F前のプレイヤーの座標を更新する
	m_vPos = m_vNextPos;

	MV1SetRotationXYZ(m_iHndl, m_ViewRot);
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetScale(m_iHndl, m_vScale);
}

void CPlayer::Draw()
{
	if (m_IsAllive && !m_IsHide) {
		MV1DrawModel(m_iHndl);
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
	//Pad
	//状態変更
	StateChange_Default_Pad();

	//キーボード操作
	Control_KeyBord(vRot);

	//ジャンプ処理
	Jamp(vRot);
}

//ジャンプ処理
void CPlayer::Jamp(VECTOR vRot)
{
	//スペースキーを押したとき
	if (CInput::IsKeyPush(KEY_INPUT_SPACE) && m_IsGround)
	{
		m_sAnimData.m_iID = ANIMID_JUMP;
	}

	if (m_sAnimData.m_iID == ANIMID_JUMP)
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
	
	if (!m_IsGround) {
		m_fGravity = GRAVITY;

		if (m_vSpd.y > -MAX_GRAVITY) {
			m_vSpd.y -= m_fGravity;
		}


		CDebugManager::GetInstance()->AddFormatString(700, 0, "プレイヤーの重力かかる前のY = %f", m_vNextPos.y);
	}
	//プレイヤーのY座標にプレイヤーのYスピードを代入
	m_vNextPos.y += m_vSpd.y;

	CDebugManager::GetInstance()->AddFormatString(700, 20, "プレイヤーの重力かかったあとのY = %f", m_vNextPos.y);
}

void CPlayer::StateChange_Default_Pad()
{
	//パッドの左スティック入力が始まったら
	if (m_PadXBuf != 0 || m_PadYBuf != 0)
	{
		//ダッシュ以外の場合
		if (m_sAnimData.m_iID != ANIMID_RUN && m_sAnimData.m_iID != ANIMID_JUMP) {
			//歩いている
			m_sAnimData.m_iID = ANIMID_RUN;
		}
	}
	//Rボタンが押されてかつプレイヤーが歩いていたら
	if (CPad::IsPadKeep(INPUT_R) && m_sAnimData.m_iID == ANIMID_RUN) {
		//状態をダッシュに変更
		m_sAnimData.m_iID = ANIMID_FAST_RUN;
	}
	//すでにダッシュだった場合
	else if (CPad::IsPadRelease(INPUT_R) && m_sAnimData.m_iID == ANIMID_FAST_RUN) {
		//歩きに戻す
		m_sAnimData.m_iID = ANIMID_RUN;
	}
}

void CPlayer::PadControl_AllState()
{
	//パッドの左スティック入力していたら
	if (m_PadXBuf != 0 || m_PadYBuf != 0)
	{
		//Rボタンが押されていたら
		if (CPad::IsPadKeep(INPUT_R)) {
			//走る
			m_sAnimData.m_iID = ANIMID_FAST_RUN;
		}
		else {
			//小走り
			m_sAnimData.m_iID = ANIMID_RUN;
		}
		
	}
	//Aボタンが押されたら
	else if (CPad::IsPadPush(INPUT_A) && m_IsGround)
	{
		//ジャンプ
		m_sAnimData.m_iID = ANIMID_JUMP;
		m_IsGround = false;
	}
	//何もしていない時
	else {
		//待機モーション
		m_sAnimData.m_iID = ANIMID_WAIT;
	}
}

void CPlayer::PadControl_Run()
{
	PadControl_AllState();

	if (CPad::IsPadPush(INPUT_A)) {
		m_sAnimData.m_iID = ANIMID_RUNNINGJUMP;
		m_IsGround = false;
	}
}


void CPlayer::Control_KeyBord(VECTOR vRot)
{
	//キーボード
	//Wキーが押されたとき
	if (CInput::IsKeyKeep(KEY_INPUT_W))
	{
		//歩いている
		m_sAnimData.m_iID = ANIMID_RUN;

		//キーが押されたフラグON
		m_IsKeyHit = true;

		//座標移動
		m_fMoveSpeed -= ADD_SPEED;

		//最大値を決定
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = DX_PI_F;
		//モデルを回転させる
		m_ViewRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_S))
	{
		//歩いている
		m_sAnimData.m_iID = ANIMID_RUN;

		//座標移動
		m_fMoveSpeed -= ADD_SPEED;

		//最大値
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			//加速
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = 0.0f * DX_PI_F / 180.0f;

		//向いている方向
		m_ViewRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_A))
	{
		//歩いている
		m_sAnimData.m_iID = ANIMID_RUN;

		//座標移動
		m_fMoveSpeed -= ADD_SPEED;

		//最大値を決定
		if (m_fMoveSpeed < -MOVE_SPEED) {
			m_fMoveSpeed = -MOVE_SPEED;
		}

		//回転値
		m_fRot = 90.0f * DX_PI_F / 180.0f;

		//向いている方向
		m_ViewRot.y = vRot.y + m_fRot;
	}
	else if (CInput::IsKeyKeep(KEY_INPUT_D))
	{
		//歩いている
		m_sAnimData.m_iID = ANIMID_RUN;

		//座標移動
		m_fMoveSpeed -= ADD_SPEED;

		//最大値
		if (m_fMoveSpeed < MOVE_SPEED)
		{
			m_fMoveSpeed = -MOVE_SPEED;
		}

		m_fRot = -90.0f * DX_PI_F / 180.0f;

		//向いている方向
		m_ViewRot.y = vRot.y + m_fRot;
	}
	else {
		m_sAnimData.m_iID = ANIMID_WAIT;
		//もしスピードが0.01以上あった場合
		if (fabs(m_fMoveSpeed) > 0.01f) {
			//離したときの止まるまでの猶予
			m_fMoveSpeed *= 0.9;
		}
		else {
			m_fMoveSpeed = 0.0f;
		}
	}

}

void CPlayer::WaitCalc()
{
	//もしスピードが0.01以上あった場合
	if (fabs(m_fMoveSpeed) > 0.01f) {
		//離したときの止まるまでの猶予
		m_fMoveSpeed *= 0.9;
	}
	else {
		//スピードを0に
		m_fMoveSpeed = 0.0f;
	}
}

void CPlayer::RunCalc()
{
	//通常スピードまで少しずつ減らす
	if (m_fMoveSpeed > -MOVE_SPEED) {
		//速さ加算
		m_fMoveSpeed -= ADD_SPEED;
	}
	else {
		//速さ加算
		m_fMoveSpeed -= ADD_SPEED;
	}
	//最大値を決定
	if (m_fMoveSpeed < -MOVE_SPEED) {
		//速さ加算
		m_fMoveSpeed = -MOVE_SPEED;
	}
}

void CPlayer::FastRunCalc()
{
	//少しずつ足していく
	m_fMoveSpeed -= ADD_SPEED;

	//プレイヤーのダッシュスピードの上限
	if (m_fMoveSpeed < -DASH_SPEED) {
		m_fMoveSpeed = -DASH_SPEED;
	}
}

void CPlayer::JumpCalc()
{

	m_vSpd.y = YSPEED;

}

void CPlayer::RuningJumpCalc()
{
	m_vSpd.y = YSPEED;
}

//何もしていないとき
void CPlayer::ExecDefault()
{
	//状態の遷移だけおこなう
	//padの操作
	PadControl_AllState();

	//歩いている状態の時
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
}

void CPlayer::ExecWait()
{
	//padの操作
	PadControl_AllState();

	//待機状態の計算処理
	WaitCalc();

	//歩いている状態の時
	if (m_sAnimData.m_iID == ANIMID_RUN)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	//ジャンプしている状態
	else if (m_sAnimData.m_iID == ANIMID_JUMP)
	{
		Request(ANIMID_JUMP, 1.0f);
		//ジャンプの計算処理
		JumpCalc();
	}
	//走っている状態の時
	else if (m_sAnimData.m_iID == ANIMID_FAST_RUN)
	{
		RequestLoop(ANIMID_FAST_RUN, 1.0f);
	}
	//ハイドモード
	if (CPad::IsPadPush(INPUT_B) && m_IsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_HIDE;
	}

	//重力処理
	Gravity();
}

//歩いているとき
void CPlayer::ExecRun()
{
	//padの操作
	PadControl_Run();

	//小走り状態の計算処理
	RunCalc();

	//待機状態
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
	//ダッシュ状態
	if (m_sAnimData.m_iID == ANIMID_FAST_RUN)
	{
		RequestLoop(ANIMID_FAST_RUN, 1.0f);
	}
	//ランニングジャンプ
	if (m_sAnimData.m_iID == ANIMID_RUNNINGJUMP)
	{
		RequestLoop(ANIMID_RUNNINGJUMP, 1.0f);
		//ジャンプ計算処理
		JumpCalc();
	}

	//隠れる操作　
	if (CPad::IsPadPush(INPUT_B) && m_IsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_IsHide = false;
	}

	//重力処理
	Gravity();
}

//走っているとき
void CPlayer::ExecFastRun()
{	
	//padの操作
	PadControl_Run();

	//ダッシュ状態の計算処理
	FastRunCalc();

	//小ダッシュ
	if (m_sAnimData.m_iID == ANIMID_RUN)
	{
		RequestLoop(ANIMID_RUN, 1.0f);
	}
	//待機状態
	if (m_sAnimData.m_iID == ANIMID_WAIT)
	{
		RequestLoop(ANIMID_WAIT, 1.0f);
	}
	//ランニングジャンプ
	if (m_sAnimData.m_iID == ANIMID_RUNNINGJUMP)
	{
		Request(ANIMID_RUNNINGJUMP, 1.0f);
		JumpCalc();
	}
	//隠れる操作
	if (CPad::IsPadPush(INPUT_B) &&  m_IsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_IsHide = false;
	}

	//重力処理
	Gravity();
}

void CPlayer::ExecJump()
{
	if (m_IsGround)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
	}
	
	if (m_IsGround) {
		//通常だったら
		if (m_sAnimData.m_iID == ANIMID_WAIT) {
			RequestLoop(ANIMID_WAIT, 1.0f);
		}
		//走っていたら
		if (m_sAnimData.m_iID == ANIMID_FAST_RUN) {
			RequestLoop(ANIMID_FAST_RUN, 1.0f);
		}
	}

	//重力処理
	Gravity();
}

void CPlayer::ExecRunningJump()
{
	if (m_IsGround)
	{
		//padの操作
		PadControl_AllState();
	}
	//padの操作
	//ダッシュ状態の計算処理
	if (m_sOldAnimData.m_iID == ANIMID_FAST_RUN) {
		FastRunCalc();
	}
	if (m_sOldAnimData.m_iID == ANIMID_RUN) {
		RunCalc();
	}

	if (m_IsGround) {
		//通常だったら
		if (m_sAnimData.m_iID == ANIMID_WAIT) {
			RequestLoop(ANIMID_WAIT, 1.0f);
		}
		//小ダッシュ
		if (m_sAnimData.m_iID == ANIMID_RUN) {
			RequestLoop(ANIMID_RUN, 1.0f);
		}
		//ダッシュ
		if (m_sAnimData.m_iID == ANIMID_FAST_RUN) {
			RequestLoop(ANIMID_FAST_RUN, 1.0f);
		}
	}

	//重力処理
	Gravity();
}

void CPlayer::ExecHide()
{
	//ハイドモード
	m_IsHide = true;

	memset(&m_vSpd, 0.0f, sizeof(m_vSpd));
	m_fMoveSpeed = 0.0f;

	if (CPad::IsPadPush(INPUT_B) && m_IsHitHideObject)
	{
		m_sAnimData.m_iID = ANIMID_WAIT;
		m_IsHide = false;
	}

	CDebugManager::GetInstance()->AddFormatString(700, 450, "ハイドモード");
}

void CPlayer::PadRotation(VECTOR vCameraRot)
{
	//左スティックが傾いているとき
	if (m_PadXBuf != 0 || m_PadYBuf != 0) {
		//スティックの角度に合わせてプレイヤーを回転
		m_fRot = atan2f((float)m_PadXBuf * -1, (float)m_PadYBuf);
		//プレイヤーを回転
		m_ViewRot.y = vCameraRot.y + m_fRot;
	}
}

void CPlayer::CalcMoveVec(VECTOR vCameraRot)
{
	//移動ベクトル計算
	m_vSpd.x = sinf(vCameraRot.y + m_fRot) * m_fMoveSpeed;
	m_vSpd.z = cosf(vCameraRot.y + m_fRot) * m_fMoveSpeed;
}

void CPlayer::AddMove()
{
	//移動速度を現在の座標に加算する
	m_vNextPos.x += m_vSpd.x;
	m_vNextPos.z += m_vSpd.z;
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

VECTOR CPlayer::GetForcsPos()
{
	VECTOR vHead = { 0 };
	VECTOR vForcus = { 0 };

	//プレイヤーの頭の座標を計算	
	vHead = VAdd(m_vPos, VGet(0, PLAYER_HEIGHT, 0));

	vHead.y += 10.0f;

	vForcus = vHead;

	return vForcus;
}

void CPlayer::ReflectCollision(VECTOR vAddVec)
{
	//オールゼロなら何もしない
	if(vAddVec.x == 0.0f && vAddVec.y == 0.0f && vAddVec.z == 0.0f) return;

	if (vAddVec.y != 0.0f) {
		m_IsGround = true;
	}

	CDebugManager::GetInstance()->AddFormatString(700, 60, "モデルのあたり判定前のY = %f", m_vNextPos.y);

	m_vNextPos = VAdd(vAddVec, m_vNextPos);
	
	CDebugManager::GetInstance()->AddFormatString(700, 80, "モデルのあたり判定後のY = %f", m_vNextPos.y);
	MV1SetPosition(m_iHndl, m_vNextPos);

	//当たった時は重力処理をしない
	m_fGravity = 0.0f;
}

