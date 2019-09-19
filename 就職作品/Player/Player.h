#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/PlayerCamera.h"

//ワールド座標で管理

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	static int remainingBalls;
	POINT basePt;
	float moveSpeed;
	std::vector <SnowBall*> snowBall_P;

	//============================================================
	//カメラの変数
	//============================================================
	static const float camHight;

	PlayerCamera *playerCam;
	//------------------------------------------------------------

	void Move(void);
	int ShootSnowball(void);

	

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
	void Draw(void);
};