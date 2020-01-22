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
	int TmpDecoCnt;

	TmpDecoCnt = decorationSpawner->Updata();

	if (TmpDecoCnt != -1)
	{
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(float(rand() % (int)StageBorder.Right), 0.0f, float(rand() % (int)StageBorder.Top));
		for (auto i = 0; i < TmpDecoCnt; i++)
		{
			GetDecorationManager.NewDecoration(&SpownPoint, (CarryObjectID)(rand() % NUM_ITEM_Dummy));
		}
	}

	int TmpEneCnt;

	TmpEneCnt = enemySpawner->Updata();

	if (TmpEneCnt != -1)
	{
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(float(rand() % (int)StageBorder.Right), 0.0f, float(rand() % (int)StageBorder.Top));
		for (auto i = 0; i < TmpEneCnt; i++)
		{
			GetEnemyManager.SetEnemy(SpownPoint);
		}
	}
}

SpawnerManager::~SpawnerManager()
{
}

