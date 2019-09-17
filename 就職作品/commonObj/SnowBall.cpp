#include "SnowBall.h"

const float SnowBall::radius = 1.5;

SnowBall::SnowBall(D3DXVECTOR3 Pos, float AngX, float AngY, float Power)
{
	mesh = resourceManager->GetXFILE("commonObj/SnowBall.x");

	D3DXMatrixTranslation(&mat, Pos.x, Pos.y + 3 , Pos.z);			//”­ŽËˆÊ’u‚Ì‰¼‚Ì’l

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(AngX))) , (Power * cos(D3DXToRadian(AngX))));

	D3DXMatrixRotationY(&rotMat, D3DXToRadian(AngY));
	mat = rotMat * mat;

	deleteTime = 5 * 60;
}

SnowBall::~SnowBall()
{
}

bool SnowBall::Update(void)
{
	if (deleteTime-- < 0)
	{
		return false;
	}

	

	D3DXMATRIX tmpMat;
	moveVec.y += -0.01;
	
	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
	mat = tmpMat * mat;

	if (mat._42 < 0.0f)
	{
		return false;
	}
	return true;
}

void SnowBall::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
