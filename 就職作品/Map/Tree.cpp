#include"Tree.h"
Tree::Tree(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Map/Tree.x");
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

Tree::~Tree()
{
}