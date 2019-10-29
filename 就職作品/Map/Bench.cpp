#include "Bench.h"

Bench::Bench(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Bench.x");
	collisionMesh = resourceManager->GetXFILE("BenchCollision.x");
	pos = Pos;
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

Bench::~Bench()
{
}

XFILE Bench::GetMesh()
{
	return collisionMesh;
}
