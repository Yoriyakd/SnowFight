#pragma once
#include<d3dx9.h>
#include"../BaseClass/XFILEObject.h"

class Player : public XFILEObject {
private:
	D3DXVECTOR3 Pos;
	int remainingBalls;

	void Move(void);
	int ShootSnowball(void);

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
};