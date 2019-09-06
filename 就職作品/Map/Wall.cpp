#include"Wall.h"

Wall::Wall(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Map/wall.x");
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

Wall::~Wall()
{

}

void Wall::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

D3DXVECTOR3 Wall::GetWallPos()
{
	return D3DXVECTOR3(pos);
}
