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
