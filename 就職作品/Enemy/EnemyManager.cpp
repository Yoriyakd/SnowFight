#include "EnemyManager.h"
#include"../GameScene/GameScene.h"

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

void EnemyManager::Update(GameScene* _GameScene)
{
	for (unsigned int i = 0; i < enemy.size(); i++)		//型推論だとsignedになるためダメみたい
	{
		enemy[i]->Update(_GameScene);
		
		for (unsigned int j = 0; j < enemy.size(); j++)
		{
			if (j == i)continue;		//同じ敵ならスキップ
			
			enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//敵同士が重ならないようにする処理
		}
	}
}
