#pragma once
#include "DxLib.h"

class CModel {
protected:
	enum Anim_State {
		ANIMSTATE_NORMAL,
		ANIMSTATE_LOOP,
		ANIMSTATE_END,
	};

	//アニメ関連のデータをまとめた構造体
	struct ANIM_DATA {
		float m_fEndFrm;			//アニメの全再生時間
		float m_fFrm;				//アニメの再生時間
		float m_fSpd;				//アニメの再生速度
		float m_fRate;				//アニメのブレンド率
		int m_iHndl;				//アニメハンドル
		int m_iID;					//再生中のアニメ
		int m_iState;				//アニメの状態
	};

	struct OLD_ANIM_DATA {
		float m_fEndFrm;			//アニメの全再生時間
		float m_fFrm;				//アニメの再生時間
		float m_fSpd;				//アニメの再生速度
		int m_iHndl;				//アニメハンドル
		int m_iID;					//再生中のアニメ
		int m_iState;				//アニメの状態
	};

	VECTOR m_vPos;					//座標
	VECTOR m_vNextPos;				//更新後の座標
	VECTOR m_vSpd;					//移動速度
	VECTOR m_vRot;					//回転角度
	VECTOR m_vScale;				//拡大縮小率
	VECTOR m_vSize;					//縦、横、奥行き
	ANIM_DATA m_sAnimData;			//アニメ再生関連データ
	ANIM_DATA m_sOldAnimData;	//更新前のアニメ再生関連データ

	int	  m_iHndl;					//モデルハンドル

	bool m_IsAllive;				//生存フラグ

public:
	//初期化
	virtual void Init();
	//数値の更新
	virtual void Update();
	//モデル描画
	virtual void Draw();
	//終了処理
	virtual void Exit();

	//画像読み込み関連
	//モデル通常ロード
	bool LoadModel(const char* pFileName);
	//モデルコピーロード
	//＠memo		:	すでに読み込んであるモデルを複数表示したい場合に使用します
	//iSrcHndl		:	読み込みたいモデルのハンドル
	bool DupilicateModel(int iSrcHndl);
	//モデルデータの削除
	void DeleteModel();

	//アニメーション関連

	//アニメアップデート
	//@memo		:	アニメ更新処理、毎回読んでください
	void UpdateAnim();

	//アニメ
	void UpdateBlendRate();

	//アニメリクエスト
	// iAnimId		:	アタッチするアニメ番号
	// iAnimSpd		:	アニメ再生速度
	// iAnimSrcHndl	:	アニメーションを持っているモデルのハンドル(-1ならばこのモデルのアニメ使用)
	// NameCheck	:	別モデルのアニメを使用する場合、モデルのフレーム名が一致していない場合
	//					アニメをアタッチするか(iAnimSrcHndl=-1の場合は無視)
	void Request(int AnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//ループアニメリクエスト
	//＠memo		:	アニメ最終フレームになったら最初に戻ります
	void RequestLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);
	//エンドループアニメリクエスト
	//@memo		:	アニメが最終フレームになっtらそのままで止まります
	void RequestendLoop(int iAnimID, float iAnimSpd, int iAnimSrcHndl = -1, bool NameCheck = false);

private:
	//安全にアニメをでタッチ
	void DetachAnim();
};
