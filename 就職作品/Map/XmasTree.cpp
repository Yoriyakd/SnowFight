#include "XmasTree.h"

XmasTree::XmasTree(D3DXVECTOR3 Pos)
{
	mesh = GetResource.GetXFILE(XmasTree_M);
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
	type = Circles;
	objRadius = 14.0f;
	
	possibleDecorate = true;
}

XmasTree::~XmasTree()
{
}
