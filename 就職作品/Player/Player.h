#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmRAnimeBase.h"
#include"ArmRAnimeMid.h"
#include"ArmRAnimeFront.h"

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
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);

private:
	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//カメラの位置からの距離
	int remainingBalls;		//残弾数
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
	XFILE armMeshR;
	D3DXMATRIX armOffsetMatR, armRotMatXR, armMatR;
	ArmRAnimeBase *ArmRAnime;

	//-----------------------------
	//作成中の雪玉
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;


	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ

	std::vector<D3DXMATRIX> ghostMat;			//飛ぶ軌道の行列			//ポインタ型で宣言しなかったら動く　なぜ？
	LPDIRECT3DTEXTURE9 GhostTex;

	//-----------------------------
	//privateメソッド
	//-----------------------------
	//Updateで呼ぶ	クリックで球が出る		引数にsnowBallManagerをポインタで渡す
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();
	void MakeGhostMat(SnowBallInitValue *snowBallInitValue);
	//呼ぶと戻り値で雪玉初期化用のデータが返ってくる
	SnowBallInitValue MakeSnowBallInitValue(void);
};