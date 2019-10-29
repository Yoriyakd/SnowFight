#include "Kamakura.h"
#include"../GameScene/GameScene.h"

void Kamakura::SpawnEnemise(void)
{
}

Kamakura::Kamakura()
{
	mesh = resourceManager->GetXFILE("Kamakura.x");
}

Kamakura::~Kamakura()
{
}

void Kamakura::SetPos(D3DXVECTOR3 Pos)
{
	pos = Pos;
}

void Kamakura::Draw(void)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

void Kamakura::Update(void)
{
	if (CoolTime < 0)
	{
		enemyManager->SetEnemy(pos);
		CoolTime = 3 * GameFPS;
	}
	CoolTime--;

	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);
}

void Kamakura::DoDamage(int DamageCnt)
{
	HP -= DamageCnt;
}
