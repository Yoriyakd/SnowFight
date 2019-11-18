#include"Tree.h"
Tree::Tree(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Tree.x");
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
	type = Circles;
	objRadius = 2.5f;
}

Tree::~Tree()
{
}
