#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"
class SnowBall {
private:
	XFILE mesh;
	D3DXMATRIX mat;
	int deleteTime;
	float power;
	static const float radius;
public:
	SnowBall(D3DXVECTOR3);
	~SnowBall();
	bool Update(void);
	void Draw(void);
};
