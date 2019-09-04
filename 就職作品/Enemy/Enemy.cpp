#include "Enemy.h"

extern ResourceManager *resourceManager;

//=====================================
//private���\�b�h
//=====================================

void Enemy::ShootSnowBall(D3DXVECTOR3)
{
}

//=====================================
//public���\�b�h
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
	return true;
}

void Enemy::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
