#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class StageHedge {
public:
	StageHedge(D3DXVECTOR3 *Pos);
	StageHedge(D3DXVECTOR3 *Pos, float Ang);
	~StageHedge();
	void Draw(void);

private:
	D3DXMATRIX mat;
	VERTEX fence[4];
	LPDIRECT3DTEXTURE9 tex;
};
