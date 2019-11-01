#include "SnowBall.h"
#include"../GameScene/GameScene.h"

const float SnowBall::radius = 1.5;
//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[(�p���[ 0~100)
SnowBall::SnowBall(SnowBallInitValue snowBallInitValue)
{
	float Power;
	Power = ((snowBallInitValue.powerRate / 100)) * 5;
	mesh = resourceManager->GetXFILE("SnowBall.x");

	D3DXMatrixTranslation(&mat, snowBallInitValue.shootPos.x, snowBallInitValue.shootPos.y , snowBallInitValue.shootPos.z);			//���ˈʒu

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(snowBallInitValue.XAxisAng))) , (Power * cos(D3DXToRadian(snowBallInitValue.XAxisAng))));

	D3DXMatrixRotationY(&rotMat, D3DXToRadian(snowBallInitValue.YAxisAng));
	mat = rotMat * mat;

	deleteTime = 10 * GameFPS;
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
	moveVec.y += Gravity;
	
	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
	mat = tmpMat * mat;

	if (mat._42 < 0.0f)				//�n�ʂɏՓ˂ŃG�t�F�N�g���� �C���X�^���X�폜
	{
		//SnowFrag�G�t�F�N�g�Ă�
		effectManager->snowFrag.push_back(new SnowFrag(D3DXVECTOR3(mat._41, mat._42, mat._43)));
		return false;
	}

	effectManager->snowLocus.push_back(new SnowLocus(mat));		//���t���[����̋O�Ղ����

	globalMoveVec = D3DXVECTOR3(mat._41, mat._42, mat._43) - memoryPos;

	memoryPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	return true;
}

void SnowBall::Draw(void)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

D3DXVECTOR3 SnowBall::GetPos()
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}

D3DXMATRIX SnowBall::GetMat()
{
	return mat;
}

D3DXVECTOR3 SnowBall::GetMoveVec()
{
	return globalMoveVec;
}

ID SnowBall::GetID()
{
	return id;
}

void SnowBall::GetCollisionSphere(CollisionSphere * CollisionSphere)
{
	CollisionSphere->pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	CollisionSphere->radius = radius;
}
