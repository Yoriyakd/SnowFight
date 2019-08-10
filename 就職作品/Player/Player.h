#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 Pos;
	int remainingBalls;

	void Move(void);
	int ShootSnowball(void);

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
	void Draw(void);
};