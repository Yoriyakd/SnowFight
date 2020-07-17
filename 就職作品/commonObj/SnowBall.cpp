#include "SnowBall.h"
#include"../GameScene/GameScene.h"
#include"../DirectX/Direct3D.h"

const float SnowBall::SPHER_RADIUS = 0.4f;
const int SnowBall::DELETE_TIME = 10;

//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[(�p���[ 0~100)
SnowBall::SnowBall(ThrowingInitValue ThrowingInitValue, ID _ID)
{
	moveVec = ThrowingInit(&ThrowingInitValue, &mat);
	mesh = GetResource.GetXFILE(SnowBall_M);
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(ThrowingInitValue.YAxisAng));		//���ˌ��̊p�x����s��쐬
	mat = rotMat * mat;

	nowDeleteTime = DELETE_TIME * GameFPS;
	id = _ID;
}

SnowBall::~SnowBall()
{
}

bool SnowBall::Update(void)
{
	if (nowDeleteTime-- < 0)			//5�b�o�߂ŏ���
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
		Effect.NewSnowFrag(D3DXVECTOR3(mat._41, mat._42, mat._43));
		return false;
	}

	Effect.NewSnowLocus(mat);		//���t���[����̋O�Ղ����
	//-----------------------------------
	//�O���[�o���ړ��x�N�g�������߂�
	//-----------------------------------
	globalMoveVec = D3DXVECTOR3(mat._41, mat._42, mat._43) - memoryPos;

	memoryPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	return true;
}

void SnowBall::Draw(void)
{
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
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
	CollisionSphere->radius = SPHER_RADIUS;
}

float SnowBall::GetSphereRadius(void)
{
	return SPHER_RADIUS;
}
