#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class Enemy {
private:
	XFILE mesh;
	D3DXMATRIX mat;

	void ShootSnowBall(D3DXVECTOR3);

public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	bool Update(void);
	void Draw(void);
};