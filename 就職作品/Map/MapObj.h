#pragma once
#include"../main.h"
class MapObj{
public:
	MapObj();
	~MapObj();
	virtual void Draw();
	D3DXMATRIX GetMat();
	virtual XFILE GetMesh();
protected:
	XFILE mesh;
	D3DXMATRIX mat;
};