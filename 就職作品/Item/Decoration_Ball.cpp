#include "Decoration_Ball.h"

Decoration_Ball::Decoration_Ball()
{
	mesh = resourceManager->GetXFILE("Decoration_Ball.x");
	picUpDistans = 8.0f;
	decorationID = RED_BALL;
}

Decoration_Ball::~Decoration_Ball()
{
}
