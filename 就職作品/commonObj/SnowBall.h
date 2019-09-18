#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"
class SnowBall {
private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	D3DXVECTOR3 moveVec;
	int deleteTime;
	
	static const float radius;
public:
	SnowBall(D3DXVECTOR3 Pos, float AngX, float AngY, float PowerPCT);			//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[
	~SnowBall();
	bool Update(void);
	void Draw(void);
};
