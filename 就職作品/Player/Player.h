#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"

//ワールド座標で管理

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, 3.0f, 0.0f);
	int remainingBalls;
	float moveSpeed;
	//-----------------------------
	//雪玉投擲関連
	//-----------------------------
	//SnowBallInitValue snowBallInitValue;
	float timeCnt = 0, shootPowerPCT;
	static const float MaxPowerTime;		//最大溜めまでにかかる時間

	//-----------------------------
	//腕
	//-----------------------------
	/*XFILE armMeshR;
	D3DXMATRIX armOffsetMatR, armRotMatXR, armMatR;
	float armAng;*/

	//-----------------------------
	//作成中の雪玉
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat;

	StageBorder stageBorder;
	
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ

	std::vector<D3DXMATRIX> ghostMat;			//飛ぶ軌道の行列			//ポインタ型で宣言しなかったら動く　なぜ？
	LPDIRECT3DTEXTURE9 GhostTex;

	//-----------------------------
	//privateメソッド
	//-----------------------------
	void Move(void);
	//Updateで呼ぶ	クリックで球が出る		引数にsnowBallManagerをポインタで渡す
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();
	void MakeGhostMat(SnowBallInitValue *snowBallInitValue);
	//呼ぶと戻り値で雪玉初期化用のデータが返ってくる
	SnowBallInitValue MakeSnowBallInitValue(void);

public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
	int GetRemainingBalls();			//残弾数を返す
	void SetStageBorder(StageBorder StageBorder);
	D3DXVECTOR3 GetPlayerPos(void);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);
};