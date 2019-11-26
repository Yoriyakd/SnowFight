#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class StageFence {
public:
	StageFence(D3DXVECTOR3 *Pos);
	StageFence(D3DXVECTOR3 *Pos, float Ang);
	~StageFence();
	void Draw(void);

private:
	D3DXMATRIX mat;
	VERTEX fence[4];
	LPDIRECT3DTEXTURE9 tex;
};
