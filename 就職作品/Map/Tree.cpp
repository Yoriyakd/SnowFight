#include"Tree.h"
Tree::Tree(D3DXVECTOR3 Pos, float Ang)
{
	mesh = resourceManager->GetXFILE("Tree.x");
	pos = Pos;

	D3DXMATRIX TmpRotMatY, TmpTransMat;
	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));

	D3DXMatrixTranslation(&TmpTransMat, Pos.x, Pos.y, Pos.z);

	mat = TmpRotMatY * TmpTransMat;
	type = Circles;
	objRadius = 2.5f;

	possibleDecorate = false;
}

Tree::~Tree()
{
}
