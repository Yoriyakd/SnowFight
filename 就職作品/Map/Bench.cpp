#include "Bench.h"

Bench::Bench(D3DXVECTOR3 Pos, float Ang)
{
	mesh = GetResource.GetXFILE(Bench_M);
	collisionMesh = GetResource.GetXFILE(BenchCollision_M);
	pos = Pos;

	D3DXMATRIX TmpRotMatY, TmpTransMat;
	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));

	D3DXMatrixTranslation(&TmpTransMat, Pos.x, Pos.y, Pos.z);

	mat = TmpRotMatY * TmpTransMat;

	type = Ray;
	objRadius = 5.5f;

	possibleDecorate = false;
}

Bench::~Bench()
{
}

XFILE Bench::GetMesh()
{
	return collisionMesh;
}

