#pragma once
#include<d3dx9.h>
#include<vector>
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"PlayerStateBase.h"
#include"PlayerStateIdle.h"
#include"ThrowState.h"
#include"WindUpState.h"
#include"MakeSnowBallState.h"
#include"../Item/DecorationManager.h"
#include"../UI/PickUpInstructions.h"
#include"../UI/AddSnowBallUI.h"
#include"CarryItem.h"

#define GetPlayer Player::GetInstance()

//------------------------------------------------------------------------
//playerのクラス
//カメラの位置にモデルを表示する。操作を受け付けて雪玉を投げる。残弾数がHPのステータス保持
//肥大化しているのでリファクタリングの必要性あり
//------------------------------------------------------------------------

//ワールド座標で管理

class Player : public SingletonBase<Player>{
	friend class SingletonBase<Player>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	bool Update(PickUpInstructions &PickUpInstructions);
	void Draw(void);

	int GetRemainingBalls();			//残弾数を返す
	const D3DXVECTOR3 GetPlayerPos(void);
	const D3DXMATRIX GetMat(void);
	void GetCollisionSphere(CollisionSphere *CollisionSphere);

	void Throw(const float PowerPCT);

	bool IsThrowAnything();
	void SetShootPower(float ShootPower);

	//雪玉を作成する	右クリック
	void MakeBallStart();
	//雪玉を作り終わる際の処理
	void MakeBallEnd();

	bool CanMakeSnowBall();
private: 
	Player();
	~Player();

	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//カメラの位置からの距離

	//-----------------------------
	//プレイヤーステータス		ここを変更して調整する
	//-----------------------------
	const int StartBallCnt = 10;	//スタート時のボールの数
	const float MakeTime = 1.5;		//作成に必要な時間
	const int AddShootAng = 25;		//雪玉を飛ばす際カメラの角度のどれくらい上に飛ばすかの角度

	//-----------------------------
	//ステータス変数
	//-----------------------------
	int remainingBalls;		//残弾数
	float shootPower;

	bool carryFlag;			//デコレーションを運んでいるか
	CarryObjectID carryObjID;		//運んでいるデコレーションの内容
	
	//-----------------------------
	//雪玉投擲関連
	//-----------------------------

	//-----------------------------
	//靴
	//-----------------------------
	XFILE shoesMesh;
	D3DXMATRIX shoesMat, shoesOffsetMat, shoesRotMatX;
	float shoesAngX;

	//-----------------------------
	//腕
	//-----------------------------
	XFILE armRMesh;
	D3DXMATRIX armROffsetMat, armRMat;

	XFILE armLMesh;
	D3DXMATRIX armLOffsetMat, armLMat;

	PlayerStateBase *playerState;		//腕のアニメーション


	//-----------------------------
	//作成中の雪玉
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

	const float MaxBallScal = 1.5;			//作成中の雪玉の最大サイズ
	float makingTimeCnt;
	bool canMakeSnowBallFlag;

	//-----------------------------
	//保持している雪玉、デコレーションの表示
	//-----------------------------
	CarryItem* carryItem;

	//-----------------------------
	//当たり判定
	//-----------------------------
	float CollisionRadius = 1.0f;		//球当たり判定の半径


	std::vector<D3DXMATRIX> ghostMat;			//飛ぶ軌道の行列
	LPDIRECT3DTEXTURE9 ghost_SnowTex, ghost_DecoTex;

	//-----------------------------
	//privateメソッド
	//-----------------------------
	
	//靴の雪玉作成時のアニメーション
	void ShoesMakeBallAnime(bool AnimeState);
	//予測線を作成する
	void MakeGhostMat();
	//呼ぶと戻り値で雪玉初期化用のデータが返ってくる
	ThrowingInitValue MakeThrowValue(const float PowerPct);
};

Player* SingletonBase<Player>::instance = nullptr;