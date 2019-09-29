#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class SkyBox {
private:
	XFILE mesh;
	D3DXMATRIX mat;
public:
	SkyBox();
	~SkyBox();
	void Draw();
};