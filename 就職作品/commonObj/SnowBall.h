#pragma once
#include<d3dx9.h>
#include"../main.h"
#include"../ResourceManager.h"
class SnowBall {
private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	D3DXVECTOR3 moveVec;
	int deleteTime;
	ID id;
	static const float radius;
public:
	SnowBall(SnowBallInitValue);			//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[
	~SnowBall();
	bool Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetMoveVec();
	ID GetID();
	void GetCollisionSphere(CollisionSphere *CollisionSphere);
};