#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"
class SnowBall {
private:
	XFILE mesh;
	D3DXMATRIX mat;
	float power;
	static const float radius;
public:
	SnowBall();
	~SnowBall();
	bool Update(void);
};
