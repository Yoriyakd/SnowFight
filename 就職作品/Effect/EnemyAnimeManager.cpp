#include "EnemyAnimeManager.h"

EnemyAnimeManager::EnemyAnimeManager()
{

}

EnemyAnimeManager::~EnemyAnimeManager()
{
	for (auto *EnemyDeathAnime : enemyDeathAnime)
	{
		delete EnemyDeathAnime;
	}
	enemyDeathAnime.clear();

	for (auto *EnemyHatAnime : enemyHatAnime)
	{
		delete EnemyHatAnime;
	}
	enemyHatAnime.clear();
}

void EnemyAnimeManager::NewEnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall)
{
	enemyDeathAnime.push_back(new EnemyDeathAnime(Enemy, SnowBall));
}

void EnemyAnimeManager::NewEnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot)
{
	enemyHatAnime.push_back(new EnemyHatAnime(Enemy, SnowBall, HeadShot));
}


void EnemyAnimeManager::Draw()
{
	for (auto *EnemyDeathAnime : enemyDeathAnime)
	{
		EnemyDeathAnime->Draw();
	}

	for (auto *EnemyHatAnime : enemyHatAnime)
	{
		EnemyHatAnime->Draw();
	}
}

void EnemyAnimeManager::Updata(void)
{
	//再生をし終わるとインスタンス削除
	for (unsigned int i = 0; i < enemyDeathAnime.size(); i++)
	{
		if (enemyDeathAnime[i]->Update() == false)
		{
			delete enemyDeathAnime[i];
			enemyDeathAnime.erase(enemyDeathAnime.begin() + i);	//配列開放
			i--;									//消した分つめる

		}
	}

	//再生をし終わるとインスタンス削除
	for (unsigned int i = 0; i < enemyHatAnime.size(); i++)
	{
		if (enemyHatAnime[i]->Update() == false)
		{
			delete enemyHatAnime[i];
			enemyHatAnime.erase(enemyHatAnime.begin() + i);	//配列開放
			i--;									//消した分つめる
		}
	}
}
