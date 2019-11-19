#include "XmasTree.h"

XmasTree::XmasTree(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("XmasTree.x");
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
	type = Circles;
	objRadius = 10.0f;
}

XmasTree::~XmasTree()
{
}
