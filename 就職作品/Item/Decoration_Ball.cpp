#include "Decoration_Ball.h"

Decoration_Ball::Decoration_Ball(const D3DXVECTOR3 * _Pos, DecorationID ID)
{
	mesh = resourceManager->GetXFILE("Decoration_Ball.x");
	pos = *_Pos;
	switch (ID)
	{
	case RED_BALL:
		color = decoration_BallColor.RED_BALL_COLOR;			//F‚ðÝ’è
		break;
	case BLUE_BALL:
		color = decoration_BallColor.BLUE_BALL_COLOR;			//F‚ðÝ’è
	case GREEN_BALL:
		color = decoration_BallColor.GREEN_BALL_COLOR;			//F‚ðÝ’è
		break;
	default:
		break;
	}

	picUpDistans = 8.0f;
	decorationID = ID;
}

Decoration_Ball::~Decoration_Ball()
{
}

void Decoration_Ball::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh, color);
}
