#include "Enemy.h"

extern ResourceManager *resourceManager;

//=====================================
//privateメソッド
//=====================================

void Enemy::ShootSnowBall(D3DXVECTOR3)
{
}

//=====================================
//publicメソッド
//=====================================

Enemy::Enemy()
{
	mesh = resourceManager->GetXFILE("Enemy/EnemyBody.x");
	D3DXMatrixTranslation(&mat, 0, 0, 10);  //仮
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
