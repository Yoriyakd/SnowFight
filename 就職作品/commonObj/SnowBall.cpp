#include "SnowBall.h"

const float SnowBall::radius = 1.5;

SnowBall::SnowBall(D3DXVECTOR3 Pos, float AngY)
{
	mesh = resourceManager->GetXFILE("commonObj/SnowBall.x");
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y + 3 , Pos.z);			//���ˈʒu�̉��̒l
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(AngY));
	mat = rotMat * mat;
	deleteTime = 5 * 60;
	power = 0;
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

	power -= 0;		//��������`��

	D3DXMATRIX tmpMat;
	
	D3DXMatrixTranslation(&tmpMat, 0, power, 0.1f);
	mat = tmpMat * mat;

	if (mat._43 < 0.0f)
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
