#include "SnowBall.h"

const float SnowBall::radius = 1.5;
//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[(�p���[ 0~100)
SnowBall::SnowBall(SnowBallInitValue snowBallInitValue)
{
	float Power;
	Power = ((snowBallInitValue.powerRate / 100)) * 5;
	mesh = resourceManager->GetXFILE("commonObj/SnowBall.x");

	D3DXMatrixTranslation(&mat, snowBallInitValue.shootPos.x, snowBallInitValue.shootPos.y , snowBallInitValue.shootPos.z);			//���ˈʒu

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(snowBallInitValue.XAxisAng))) , (Power * cos(D3DXToRadian(snowBallInitValue.XAxisAng))));

	D3DXMatrixRotationY(&rotMat, D3DXToRadian(snowBallInitValue.YAxisAng));
	mat = rotMat * mat;

	deleteTime = 5 * FPS;
	id = snowBallInitValue.id;
}

SnowBall::~SnowBall()
{
}

bool SnowBall::Update(void)
{
	if (deleteTime-- < 0)			//5�b�o�߂ŏ���
	{
		return false;
	}

	

	D3DXMATRIX tmpMat;
	moveVec.y += -0.02f;
	
	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
	mat = tmpMat * mat;

	if (mat._42 < 0.0f)				//�n�ʂɏՓ˂ŏ���
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

D3DXVECTOR3 SnowBall::GetMoveVec()
{
	return moveVec;
}

ID SnowBall::GetID()
{
	return id;
}

void SnowBall::GetCollisionSphere(CollisionSphere * CollisionSphere)
{
	CollisionSphere->pos = D3DXVECTOR3(mat._41, mat._42 + 2, mat._43);
	CollisionSphere->radius = radius;
}
