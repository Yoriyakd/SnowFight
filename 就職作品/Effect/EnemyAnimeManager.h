#pragma once
#include"../main.h"
#include<vector>
#include"EnemyDeathAnime.h"
#include"EnemyHatAnime.h"
#include"../commonObj/SnowBall.h"
#include"../Enemy/Enemy.h"

class EnemyAnimeManager {
public:
	EnemyAnimeManager();
	~EnemyAnimeManager();

	void NewEnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall);
	void NewEnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot);

	void Draw(void);
	void Updata(void);

private:
	std::vector<EnemyDeathAnime*> enemyDeathAnime;
	std::vector<EnemyHatAnime*> enemyHatAnime;
};