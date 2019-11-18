#pragma once
#include"../main.h"
#include"../ResourceManager.h"

class Ground {
public:
	Ground();
	~Ground();
	D3DXMATRIX GetMat();
	void SetMat(D3DXMATRIX);
	void  Draw();

private:
	VERTEX ground[4];
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
};
