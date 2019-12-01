#include "Bobbin_Red.h"

Bobbin_Red::Bobbin_Red(D3DXVECTOR3 Pos, float Ang)
{
	mesh = resourceManager->GetXFILE("Bobbin_Red.x");
	pos = Pos;

	D3DXMATRIX TmpRotMatY, TmpTransMat;
	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));

	D3DXMatrixTranslation(&TmpTransMat, Pos.x, Pos.y, Pos.z);

	mat = TmpRotMatY * TmpTransMat;

	type = Circles;
	objRadius = 1.5f;

	possibleDecorate = false;
}

Bobbin_Red::~Bobbin_Red()
{
}
