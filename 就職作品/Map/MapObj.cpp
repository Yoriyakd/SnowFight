#include "MapObj.h"

MapObj::MapObj()
{
}

MapObj::~MapObj()
{
}

void MapObj::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

D3DXMATRIX MapObj::GetMat()
{
	return mat;
}

XFILE MapObj::GetMesh()
{
	return mesh;
}
