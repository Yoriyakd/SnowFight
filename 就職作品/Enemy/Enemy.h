#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
class Enemy {
private:
	XFILE mesh;
	D3DXMATRIX mat;
	virtual void ShootSnowBall(void);
protected:
	//static std::vector <SnowBall*> snowBall_E;

	

public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(void);
	virtual void Draw(void);
	virtual D3DXVECTOR3 GetPos(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
};