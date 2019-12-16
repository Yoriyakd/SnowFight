#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmAnimeBase.h"
#include"ArmAnimeMid.h"
#include"ThrowAnime.h"
#include"WindUpAnime.h"
#include"MakeSnowBallAnime.h"
#include"../Item/DecorationManager.h"
#include"../UI/PickUpInstructions.h"

//ワールド座標で管理

class Player {
public:
	Player();
	~Player();
	bool Update(SnowBallManager &SnowBallManager, DecorationManager &DecorationManager, PickUpInstructions &PickUpInstructions);
	void SetCamera(void);
	void Draw(void);

	int GetRemainingBalls();			//残弾数を返す
	D3DXVECTOR3 GetPlayerPos(void);
	void GetCollisionSphere(CollisionSphere *CollisionSphere);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);

	void HitSnowBall();
	int GetHP();

private:
	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//カメラの位置からの距離

	//-----------------------------
	//プレイヤーステータス		ここを変更して調整する
	//-----------------------------
	const int StartBallCnt = 10;	//スタート時のボールの数
	const float MakeTime = 1.5;		//作成に必要な時間
	const float MaxPowerTime = 1.5f;	//最大溜めまでにかかる時間
	int HP = 10;


	//-----------------------------
	//ステータス変数
	//-----------------------------
	int remainingBalls;		//残弾数

	bool carryFlag;			//デコレーションを運んでいるか
	DecorationID carryDecorationID;		//運んでいるデコレーションの内容
	
	//-----------------------------
	//雪玉投擲関連
	//-----------------------------
	float timeCnt = 0, shootPowerPCT;

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

	ArmAnimeBase *ArmAnime;		//腕のアニメーション


	//-----------------------------
	//作成中の雪玉
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

	const float MaxBallScal = 1.5;			//作成中の雪玉の最大サイズ

	//-----------------------------
	//当たり判定
	//-----------------------------
	float CollisionRadius = 1.0f;		//球当たり判定の半径

	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ

	std::vector<D3DXMATRIX> ghostMat;			//飛ぶ軌道の行列
	LPDIRECT3DTEXTURE9 GhostTex;

	

	//-----------------------------
	//privateメソッド
	//-----------------------------
	//Updateで呼ぶ	左クリックで球かデコレーションが出る		引数にsnowBallManagerをポインタで渡す
	void Throw(SnowBallManager &snowBallManager, DecorationManager &decorationManager);
	//雪玉を作成する	右クリック
	void MakeBall();
	//靴の雪玉作成時のアニメーション
	void ShoesMakeBallAnime(bool AnimeState);
	//予測線を作成する
	void MakeGhostMat(ThrowingInitValue *ThrowingInitValue);
	//呼ぶと戻り値で雪玉初期化用のデータが返ってくる
	ThrowingInitValue MakeThrowValue(void);
};