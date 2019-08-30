#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	static int remainingBalls;
	POINT basePt;
	//============================================================
	//ƒJƒƒ‰‚Ì•Ï”
	//============================================================
	float camAngY, camAngX;			//ŒX‚«‚Ì—Ê‚ğ“ü‚ê‚é	‰ñ“]²‚Å–¼‘O•t‚¯
	D3DXMATRIX camRotMatY, camRotMatX, camRotMat;

	void Move(void);
	int ShootSnowball(void);

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
	void Draw(void);
};