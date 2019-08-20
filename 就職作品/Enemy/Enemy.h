#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class Enemy {
private:
	XFILE mesh;
	D3DXMATRIX mat;

	void ShootSnowBall(D3DXVECTOR3);

public:
	Enemy();
	~Enemy();
	bool Update(void);
	void Draw(void);
};