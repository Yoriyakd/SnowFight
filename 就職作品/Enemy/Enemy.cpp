#include "Enemy.h"

extern ResourceManager *resourceManager;

//=====================================
//privateメソッド
//=====================================

void Enemy::ShootSnowBall(void)
{
	//snowBall_E.push_back(new SnowBall(D3DXVECTOR3(mat._41, mat._42, mat._43), 0, 180, 50));
}

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy(D3DXVECTOR3 Pos)
{
	mesh = resourceManager->GetXFILE("Enemy/EnemyBody.x");
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

Enemy::~Enemy()
{
}

bool Enemy::Update(void)
{
	ShootSnowBall();
	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

D3DXVECTOR3 Enemy::GetPos(void)
{
	return D3DXVECTOR3(mat._41, mat._42, mat._43);
}
