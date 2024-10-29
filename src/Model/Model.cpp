#include "Model.h"


//初期化
void CModel::Init()
{
	Exit();
	//ひとまず初期化していく
	memset(&m_vPos, 0.0f, sizeof(VECTOR));			//座標
	memset(&m_vNextPos, 0.0f, sizeof(VECTOR));		//更新後の座標
	memset(&m_vRot, 0.0f, sizeof(VECTOR));			//回転速度
	memset(&m_vSpd, 0.0f, sizeof(VECTOR));			//速さ
	memset(&m_vScale, 0.0f, sizeof(VECTOR));		//拡大縮小率
	memset(&m_vSize, 0.0f, sizeof(VECTOR));			//縦、横、奥行き	
	memset(&m_IsAllive, true, sizeof(bool));		//生存フラグ
	m_iHndl = -1;									//プレイヤーのモデルハンドル

	ZeroMemory(&m_sAnimData, sizeof(m_sAnimData));
	ZeroMemory(&m_sOldAnimData, sizeof(m_sOldAnimData));
	m_sAnimData.m_iHndl = -1;						//アニメデータのモデルハンドル
	m_sAnimData.m_iID = -0;							//アニメデータのアニメ番号
	m_sOldAnimData.m_iHndl = -1;					//更新前のアニメデータのモデルハンドル
	m_sOldAnimData.m_iID = -0;						//更新前のアニメデータのアニメ番号
}

//終了処理
void CModel::Exit()
{
	DeleteModel();
}

//更新処理
void CModel::Update()
{
	MV1SetPosition(m_iHndl, m_vPos);
	MV1SetRotationXYZ(m_iHndl, m_vRot);
	MV1SetScale(m_iHndl, m_vScale);
}

bool CModel::LoadModel(const char* pFileName)
{
	if (m_iHndl != -1) {
		return false;				//モデルの読み込み済み
	}
	m_iHndl = MV1LoadModel(pFileName);
	if (m_iHndl == -1) {
		return false;				//モデルの読み込み
	}
	return true;
}

void CModel::Draw()
{

}

//コピーデータ読み込み
bool CModel::DupilicateModel(int iSrcHndl)
{
	if (m_iHndl != -1) {
		return false;				//モデル読み込み済み
	}
	m_iHndl = MV1DuplicateModel(iSrcHndl);
	if (m_iHndl == -1) {
		return false;				//モデル読み込み失敗
	}

	return true;
}

void CModel::DeleteModel()
{
	if (m_iHndl == -1)
	{
		return;
	}
	MV1DeleteModel(m_iHndl);
	m_iHndl = -1;
}

//アニメリクエスト
void CModel::Request(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	//アニメーションでタッチ
	DetachAnim();

	//アニメ再生&各種データをセット
	m_sAnimData.m_iHndl = MV1AttachAnim(m_iHndl, iAnimID, iAnimSrcHndl, NameCheck);
	m_sAnimData.m_iID = iAnimID;
	m_sAnimData.m_fEndFrm = MV1GetAnimTotalTime(m_iHndl, iAnimID);
	m_sAnimData.m_fFrm = 0.0f;
	m_sAnimData.m_fSpd = fAnimSpd;
	m_sAnimData.m_iState = ANIMSTATE_NORMAL;
}

//ループリクエスト
void CModel::RequestLoop(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, fAnimSpd, iAnimSrcHndl, NameCheck);
	//ここだけループする
	m_sAnimData.m_iState = ANIMSTATE_LOOP;
}

//エンドループリクエスト
void CModel::RequestendLoop(int iAnimID, float fAnimSpd, int iAnimSrcHndl, bool NameCheck)
{
	Request(iAnimID, fAnimSpd, iAnimSrcHndl, NameCheck);
	//ここだけエンドループに変える
	m_sAnimData.m_iState = ANIMSTATE_END;
}


//アニメーションデタッチ
void CModel::DetachAnim()
{
	if (m_sAnimData.m_iHndl != -1)
	{
		MV1DetachAnim(m_iHndl, m_sAnimData.m_iHndl);
		m_sAnimData.m_iHndl = -1;
	}
}

void CModel::UpdateBlendRate()
{
	if (m_sOldAnimData.m_iID != -1) {

		m_sAnimData.m_fRate += 0.1f;

		MV1SetAttachAnimBlendRate(m_iHndl, m_sOldAnimData.m_iID, 1.0 - m_sAnimData.m_fRate);
		MV1SetAttachAnimBlendRate(m_iHndl, m_sAnimData.m_iID, m_sAnimData.m_fRate);

		if (m_sAnimData.m_fRate >= 1.0f) {
			MV1DetachAnim(m_iHndl, m_sOldAnimData.m_iID);
			m_sOldAnimData.m_iID = -1;
		}
	}
}

//アニメアップデータ
void CModel::UpdateAnim()
{
	if (m_sAnimData.m_iHndl == -1) { return; }	//アニメーションが再生されていない

	//アニメーション速度更新
	m_sAnimData.m_fFrm += m_sAnimData.m_fSpd;

	if (m_sAnimData.m_fFrm >= m_sAnimData.m_fEndFrm)
	{
		//最終フレームまで来たら、状態に合わせて動作を変える
		switch (m_sAnimData.m_iState)
		{
		//通常は終了させる
		case ANIMSTATE_NORMAL:
			DetachAnim();
			m_sAnimData.m_fEndFrm = 0.0f;
			m_sAnimData.m_fFrm = 0.0f;
			m_sAnimData.m_fSpd = 0.0f;
			return;
			//ループをモデル
		case ANIMSTATE_LOOP:
			m_sAnimData.m_fFrm = 0.0f;
			break;
			//エンドループ最後で止める
		case ANIMSTATE_END:
			m_sAnimData.m_fFrm = m_sAnimData.m_fEndFrm;
			break;
		}
	}

	//再生時間設定
	MV1SetAttachAnimTime(m_iHndl, m_sAnimData.m_iHndl, m_sAnimData.m_fFrm);
}