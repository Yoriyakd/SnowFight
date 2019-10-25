#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		delete enemy[i];
	}
	enemy.clear();
}

void EnemyManager::SetEnemy(D3DXVECTOR3 Pos)
{
	enemy.push_back(new Enemy(Pos));
}

void EnemyManager::Draw()
{
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw();
	}
}

void EnemyManager::Update(SnowBallManager *SnowBallManager)
{
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(SnowBallManager);
		D3DXVECTOR3 PushOutVec;
		for (unsigned int j = 0; j < enemy.size(); j++)
		{
			PushOutVec = enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//“G“¯m‚ªd‚È‚ç‚È‚¢‚æ‚¤‚É‚·‚éˆ—
		}
	}

	
}
