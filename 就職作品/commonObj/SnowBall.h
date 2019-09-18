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
	SnowBall(D3DXVECTOR3 Pos, float AngX, float AngY, float PowerPCT);			//発射位置、発射角度、発射方向、発射パワー
	~SnowBall();
	bool Update(void);
	void Draw(void);
};
