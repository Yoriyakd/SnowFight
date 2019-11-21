#include "Decoration_Ball.h"

Decoration_Ball::Decoration_Ball(const D3DXVECTOR3 * _Pos)
{
	mesh = resourceManager->GetXFILE("Decoration_Ball.x");
	pos = *_Pos;
	picUpDistans = 8.0f;
	decorationID = RED_BALL;
}

Decoration_Ball::~Decoration_Ball()
{
}
