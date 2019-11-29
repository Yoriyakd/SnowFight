#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmAnimeBase.h"
#include"ArmRAnimeMid.h"
#include"ThrowRAnime.h"
#include"WindUpRAnime.h"
#include"ArmLWalkAnime.h"
#include"../Item/DecorationManager.h"

//ワールド座標で管理

class Player {
public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
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
	//プレイヤーステータス
	//-----------------------------
	int remainingBalls;		//残弾数

	bool carryFlag;			//デコレーションを運んでいるか
	DecorationID carryDecorationID;		//運んでいるデコレーションの内容

	int HP = 10;
	//-----------------------------
	//雪玉投擲関連
	//-----------------------------
	float timeCnt = 0, shootPowerPCT;
	static const float MaxPowerTime;		//最大溜めまでにかかる時間

	//-----------------------------
	//靴
	//-----------------------------
	XFILE shoesMesh;
	D3DXMATRIX shoesMat, shoesOffsetMat;

	//-----------------------------
	//腕
	//-----------------------------
	XFILE armRMesh;
	D3DXMATRIX armROffsetMat, armRMat;
	ArmAnimeBase *ArmRAnime;		//右腕のアニメーション

	XFILE armLMesh;
	D3DXMATRIX armLOffsetMat, armLMat;
	ArmAnimeBase *ArmLAnime;		//左腕のアニメーション


	//-----------------------------
	//作成中の雪玉
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

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
	//Updateで呼ぶ	右クリックで球かデコレーションが出る		引数にsnowBallManagerをポインタで渡す
	void Throw(SnowBallManager *snowBallManager);
	//雪玉を作成する	左クリック
	void MakeBall();
	//予測線を作成する
	void MakeGhostMat(ThrowingInitValue *ThrowingInitValue);
	//呼ぶと戻り値で雪玉初期化用のデータが返ってくる
	ThrowingInitValue MakeThrowValue(void);
};