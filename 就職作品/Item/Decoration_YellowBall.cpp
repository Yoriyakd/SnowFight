#include"Decoration_YellowBall.h"

Decoration_YellowBall::Decoration_YellowBall(const D3DXVECTOR3 * _Pos)
{
	mesh = resourceManager->GetXFILE("Decoration_YellowBall.x");
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = YELLOW_BALL;
}

Decoration_YellowBall::~Decoration_YellowBall()
{
}

void Decoration_YellowBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}