#include "Decoration_BlueBall.h"

Decoration_BlueBall::Decoration_BlueBall(const D3DXVECTOR3 * _Pos)
{
	mesh = resourceManager->GetXFILE("Decoration_BlueBall.x");
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = BLUE_BALL;
}

Decoration_BlueBall::~Decoration_BlueBall()
{
}

void Decoration_BlueBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
