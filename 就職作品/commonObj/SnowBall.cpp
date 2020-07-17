#include "SnowBall.h"
#include"../GameScene/GameScene.h"
#include"../DirectX/Direct3D.h"

const float SnowBall::SPHER_RADIUS = 0.4f;
const int SnowBall::DELETE_TIME = 10;

//発射位置、発射角度、発射方向、発射パワー(パワー 0~100)
SnowBall::SnowBall(ThrowingInitValue ThrowingInitValue, ID _ID)
{
	moveVec = ThrowingInit(&ThrowingInitValue, &mat);
	mesh = GetResource.GetXFILE(SnowBall_M);
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(ThrowingInitValue.YAxisAng));		//発射元の角度から行列作成
	mat = rotMat * mat;

	nowDeleteTime = DELETE_TIME * GameFPS;
	id = _ID;
}

SnowBall::~SnowBall()
{
}

bool SnowBall::Update(void)
{
	if (nowDeleteTime-- < 0)			//5秒経過で消滅
	{
		return false;
	}

	D3DXMATRIX tmpMat;
	moveVec.y += SnowBallGravity;
	
	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);
	mat = tmpMat * mat;

	if (mat._42 < 0.0f)				//地面に衝突でエフェクト発生 インスタンス削除
	{
		//SnowFragエフェクト呼ぶ
		Effect.NewSnowFrag(D3DXVECTOR3(mat._41, mat._42, mat._43));
		return false;
	}

	Effect.NewSnowLocus(mat);		//毎フレーム雪の軌跡を作る
	//-----------------------------------
	//グローバル移動ベクトルを求める
	//-----------------------------------
	globalMoveVec = D3DXVECTOR3(mat._41, mat._42, mat._43) - memoryPos;

	memoryPos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	return true;
}

void SnowBall::Draw(void)
{
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
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
