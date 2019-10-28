#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"../commonObj/PlayerCamera.h"

//ワールド座標で管理

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	int remainingBalls;
	float moveSpeed;

	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat;

	StageBorder stageBorder;
	
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ

	std::vector<D3DXMATRIX> ghostMat;			//飛ぶ軌道の行列			//ポインタ型で宣言しなかったら動く　なぜ？
	LPDIRECT3DTEXTURE9 GhostTex;

	void Move(void);
	//Updateで呼ぶ	クリックで球が出る		引数にsnowBallManagerをポインタで渡す
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();
	void MakeGhostMat(SnowBallInitValue *snowBallInitValue);
	

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