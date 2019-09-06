#include "SnowBall.h"

const float SnowBall::radius = 1.5;

SnowBall::SnowBall()
{
	mesh = resourceManager->GetXFILE("SnowBall.x");
}

SnowBall::~SnowBall()
{
}

bool SnowBall::Update(void)
{
	static float powerTest = 5;	//test	•ú•¨ü‚ğ•`‚­ˆ—‚É’u‚«Š·‚¦‚é
	powerTest -= 0.8;			//test

	D3DXMATRIX tmpMat;
	
	D3DXMatrixTranslation(&tmpMat, 0, powerTest, 0.5f);
	mat = tmpMat * mat;

	if (mat._43 < 0.0f)
	{
		return false;
	}
	return true;
}

void SnowBall::Draw(void)
{
}
