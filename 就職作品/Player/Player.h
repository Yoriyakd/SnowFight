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
	

	//============================================================
	//カメラの変数
	//============================================================
	static const float camHight;

	PlayerCamera *playerCam;
	//------------------------------------------------------------

	void Move(void);
	//Updateで呼ぶ	クリックで球が出る		引数にsnowBallManagerをポインタで渡す
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();

	

public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
	int GetRemainingBalls();			//残弾数を返す
	void SetStageBorder(StageBorder StageBorder);
};