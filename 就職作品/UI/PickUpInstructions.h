#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"
class PickUpInstructions {
public:
	PickUpInstructions();
	~PickUpInstructions();
	//2D•\Ž¦
	void Draw();
	void TurnOnDisplay(void);
	void TurnOffDisplay(void);
private:
	bool displayFlag;
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
};