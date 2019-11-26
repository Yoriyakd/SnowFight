#include "Bench.h"

Bench::Bench(D3DXVECTOR3 Pos, float Ang)
{
	mesh = resourceManager->GetXFILE("Bench.x");
	collisionMesh = resourceManager->GetXFILE("BenchCollision.x");
	pos = Pos;

	D3DXMATRIX TmpRotMatY, TmpTransMat;
	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));

	D3DXMatrixTranslation(&TmpTransMat, Pos.x, Pos.y, Pos.z);

	mat = TmpRotMatY * TmpTransMat;

	type = Ray;
	objRadius = 1.5f;
}

Bench::~Bench()
{
}

XFILE Bench::GetMesh()
{
	return collisionMesh;
}

