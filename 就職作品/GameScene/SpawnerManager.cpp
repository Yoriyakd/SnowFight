#include "SpawnerManager.h"

void SpawnerManager::EnemySpawnerInitialize(SpawnerData& SpawnerData)
{
	if (enemySpawner == nullptr)
	{
		enemySpawner = new GameObjectSpawner();
	}
	enemySpawner->Initialize(SpawnerData);
}

void SpawnerManager::DecorationSpawnerInitialize(SpawnerData& SpawnerData)
{
	if (decorationSpawner == nullptr)
	{
		decorationSpawner = new GameObjectSpawner();
	}
	decorationSpawner->Initialize(SpawnerData);
}

void SpawnerManager::Update(StageBorder& StageBorder)
{
	int TmpCnt;

	TmpCnt = decorationSpawner->Updata();

	if (TmpCnt != -1)
	{
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(float(rand() % (int)StageBorder.Right), 0.0f, float(rand() % (int)StageBorder.Top));
		for (auto i = 0; i < TmpCnt; i++)
		{
			GetDecorationManager.NewDecoration(&SpownPoint, (DecorationID)(rand() % NUM_ITEM));
		}
	}


	TmpCnt = enemySpawner->Updata();

	if (TmpCnt != -1)
	{
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(float(rand() % (int)StageBorder.Right), 0.0f, float(rand() % (int)StageBorder.Top));
		for (auto i = 0; i < TmpCnt; i++)
		{
			GetEnemyManager.SetEnemy(SpownPoint);
		}
	}
}

SpawnerManager::~SpawnerManager()
{
}

