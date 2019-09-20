#include "SnowBall.h"

const float SnowBall::radius = 1.5;
//発射位置、発射角度、発射方向、発射パワー(パワー 0~100)
SnowBall::SnowBall(D3DXVECTOR3 Pos, float AngX, float AngY, float PowerPCT)
{
	float Power;
	Power = ((PowerPCT / 100)) * 5;
	mesh = resourceManager->GetXFILE("commonObj/SnowBall.x");

	D3DXMatrixTranslation(&mat, Pos.x, Pos.y + 3 , Pos.z);			//発射位置の仮の値

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(AngX))) , (Power * cos(D3DXToRadian(AngX))));

	D3DXMatrixRotationY(&rotMat, D3DXToRadian(AngY));
	mat = rotMat * mat;

	deleteTime = 5 * FPS;
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
	moveVec.y += -0.02;
	
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

D3DXVECTOR3 SnowBall::GetPos()
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}
