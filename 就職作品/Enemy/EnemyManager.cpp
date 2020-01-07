#include "EnemyManager.h"

EnemyManager::~EnemyManager()
{
	AllDelete();
}

void EnemyManager::AllDelete(void)
{
	for (auto *Enemy : enemy)
	{
		delete Enemy;
	}
	enemy.clear();
}

void EnemyManager::DeleteEnemyInstance(unsigned int ite)
{
	delete enemy[ite];
	enemy.erase(enemy.begin() + ite);
}

void EnemyManager::SetEnemy(D3DXVECTOR3 Pos)
{
	enemy.push_back(new Enemy(Pos));
}

void EnemyManager::Draw()
{
	for (auto *Enemy : enemy)
	{
		Enemy->Draw();
	}
}

void EnemyManager::Update(Player & Player, SnowBallManager & SnowBallManager, StageBorder & StageBorder)
{
	for (unsigned int i = 0; i < enemy.size(); i++)		//型推論だとsignedになるためダメみたい
	{
		enemy[i]->Update(Player, SnowBallManager, StageBorder);
		//D3DXVECTOR3 PushOutVec;		//押されたときに移動するベクトル ☆
		for (unsigned int j = 0; j < enemy.size(); j++)
		{
			if (j == i)continue;		//同じ敵ならスキップ
			//PushOutVec = enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//敵同士が重ならないようにする処理　☆両方押されるようにするときつかう
			enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//敵同士が重ならないようにする処理
		}
	}
}
