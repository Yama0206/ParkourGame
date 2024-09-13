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
 	//情報を入れる
	void SetInfo(VECTOR vPos, VECTOR vSize, VECTOR vRot);
};