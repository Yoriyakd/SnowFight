#pragma once
#include"../main.h"
class MapObj{
private:
protected:
	XFILE mesh;
	D3DXMATRIX mat;
public:
	MapObj();
	~MapObj();
	virtual void Draw();
	D3DXMATRIX GetMat();
	XFILE GetMesh();
};