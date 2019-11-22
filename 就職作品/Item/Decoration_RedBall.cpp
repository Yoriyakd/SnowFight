#include "Decoration_RedBall.h"

Decoration_RedBall::Decoration_RedBall(const D3DXVECTOR3 * _Pos)
{
	mesh = resourceManager->GetXFILE("Decoration_RedBall.x");
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = RED_BALL;
}

Decoration_RedBall::~Decoration_RedBall()
{
}

void Decoration_RedBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
