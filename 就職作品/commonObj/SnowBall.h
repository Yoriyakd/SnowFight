#pragma once
#include<d3dx9.h>
#include"../main.h"
#include"../ResourceManager.h"
#include"../Effect/EffectManager.h"
class SnowBall {
public:
	SnowBall(ThrowingInitValue, ID);			//発射位置、発射角度、発射方向、発射パワー
	~SnowBall();
	bool Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos();
	D3DXMATRIX GetMat();
	D3DXVECTOR3 GetMoveVec();				//グローバルの移動ベクトルを渡す
	ID GetID();
	void GetCollisionSphere(CollisionSphere *CollisionSphere);
	float GetSphereRadius(void);

private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	D3DXVECTOR3 moveVec, memoryPos, globalMoveVec;
	const static int DELETE_TIME;
	int nowDeleteTime;
	ID id;
	const static float SPHER_RADIUS;				//当たり判定に使う球の半径
};