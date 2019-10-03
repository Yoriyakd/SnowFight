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
	static int remainingBalls;
	float moveSpeed;
	

	//============================================================
	//カメラの変数
	//============================================================
	static const float camHight;
	POINT basePt;

	PlayerCamera *playerCam;
	//------------------------------------------------------------

	void Move(void);
	int ShootSnowball(SnowBallManager *snowBallManager);

	

public:
	//std::vector <SnowBall*> snowBall_P;

	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
};