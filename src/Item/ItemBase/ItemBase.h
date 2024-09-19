#pragma once
#include "DxLib.h"

enum eType
{
	Coin = 1,

};


class CItemBase
{
protected:
	VECTOR m_vPos;		//座標
	VECTOR m_vRot;		//回転値
	VECTOR m_vSize;		//モデルサイズ
	VECTOR m_vScale;	//拡縮率
	
	int m_iHndl;		//モデルハンドル
	bool m_IsAllive;	//生存フラグ

	int iAngleCnt;		//アイテムが回転するときのカウント変数

public:
	//読み込み
	void Load(int iModelHndl);
	//描画
	void Draw();
	//更新処理
	void Update();

 	//設定
	void SetInfo(VECTOR vPos, VECTOR vRot, VECTOR vSize, VECTOR vScale, int IsAllive);		//情報
	bool SetIsAllive(bool IsFrag) { return m_IsAllive = IsFrag; }							//生存フラグ

	//取得
	VECTOR GetPosVec() { return m_vPos; }		//座標取得
	VECTOR GetSizeVec() { return m_vSize; }		//サイズ取得

};