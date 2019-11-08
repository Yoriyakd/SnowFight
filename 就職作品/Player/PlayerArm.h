#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"PlayerCamera.h"
class PlayerArm {
private:
	XFILE armMeshR;
	D3DXMATRIX armOffsetMatR, armRotMatXR, armMatR;
	float armAng;
public:
	PlayerArm();
	~PlayerArm();
	void Draw(void);
	void Update(void);
};