#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"

//ワールド座標で管理

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	static int remainingBalls;
	POINT basePt;
	float moveSpeed;
	//============================================================
	//カメラの変数
	//============================================================
	float camAngY, camAngX;			//傾きの量を入れる	回転軸で名前付け
	D3DXMATRIX camRotMatY, camRotMatX, camRotMat;

	void Move(void);
	int ShootSnowball(void);

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
	void Draw(void);
};