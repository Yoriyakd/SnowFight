#include "SnowBall.h"
#include"../GameScene/GameScene.h"

//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[(�p���[ 0~100)
SnowBall::SnowBall(ThrowingInitValue ThrowingInitValue, ID _ID)
{
	moveVec = ThrowingInit(&ThrowingInitValue, &mat);
	mesh = GetResource.GetXFILE(SnowBall_M);
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(ThrowingInitValue.YAxisAng));		//���ˌ��̊p�x����s��쐬
	mat = rotMat * mat;

	deleteTime = 10 * GameFPS;
	id = _ID;
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
	moveVec.y += SnowBallGravity;
	
	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
	mat = tmpMat * mat;

	if (mat._42 < 0.0f)				//�n�ʂɏՓ˂ŃG�t�F�N�g���� �C���X�^���X�폜
	{
		//SnowFrag�G�t�F�N�g�Ă�
		effectManager->NewSnowFrag(D3DXVECTOR3(mat._41, mat._42, mat._43));
		return false;
	}

	effectManager->NewSnowLocus(mat);		//���t���[����̋O�Ղ����
	//-----------------------------------
	//�O���[�o���ړ��x�N�g�������߂�
	//-----------------------------------
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
	CollisionSphere->radius = SphereRadius;
}

float SnowBall::GetSphereRadius(void)
{
	return SphereRadius;
}
