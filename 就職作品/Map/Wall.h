#pragma once
#include"../main.h"
#include"../ResourceManager.h"

class Wall {
private:
	XFILE mesh;
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
public:
	Wall(D3DXVECTOR3);
	~Wall();
	void Draw(void);
	D3DXMATRIX GetWallMat();
	XFILE GetMesh();
};
